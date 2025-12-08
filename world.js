function getModelBounds(obj) {
    let minX = Infinity, minY = Infinity, minZ = Infinity;
    let maxX = -Infinity, maxY = -Infinity, maxZ = -Infinity;

    for (let v of obj.vertices) {
        minX = Math.min(minX, v.x);
        minY = Math.min(minY, v.y);
        minZ = Math.min(minZ, v.z);
        maxX = Math.max(maxX, v.x);
        maxY = Math.max(maxY, v.y);
        maxZ = Math.max(maxZ, v.z);
    }

    return {
        min: { x: minX, y: minY, z: minZ },
        size: { x: maxX - minX, y: maxY - minY, z: maxZ - minZ }
    };
}


function getStretchScale(model, targetSize) {
    const b = getModelBounds(model);

    return createVector(
        targetSize.x / (b.size.x || 1),
        targetSize.y / (b.size.y || 1),
        targetSize.z / (b.size.z || 1)
    );
}


export class World {
    constructor() {
        this.cubes = [];
        this.creatures = [];
        this.models = { player: {} };
        this.modelBounds = { player: {} };
        this.lastAnimTime = 0;

        this.RUN_FRAMES = 5;
        this.USE_FRAMES = 3;
        this.FRAME_INTERVAL = 120;
        this.GRAVITY = 0.6;
        this.GROUND_Y = -40;
        this.STEP_HEIGHT = 5;
        this.PUSH_FORCE = 1.5;
    }

    new_cube(pos, size, weight = -1, texture = null, model = null, wireframe = false) {
        this.cubes.push({
            pos,
            size,
            weight,
            texture,
            model,
            wireframe,
            vel: createVector(0, 0, 0)
        });
    }

    new_creature(opts) {
        const ent = {
            position: opts.position.copy(),
            size: opts.size || createVector(40, 80, 40),
            state: opts.state || "idle",
            frame: 0,
            rotation: 0,
            vel: createVector(0, 0, 0),
            npc: opts.npc || false,
            dirVec: opts.dirVec || createVector(0, 0, 0),
            speed: opts.speed || 0,
            spawnPos: opts.spawnPos || null,
            targetPos: opts.targetPos || null,
            traveling: opts.traveling || false,
            arrivedAt: 0,
            respawnDelay: opts.respawnDelay || 1200,
            startDelay: opts.startDelay || 0,
            modelScale: opts.modelScale || 1,
            onGround: false,
            _lastAnimTime: millis(),
            strength: opts.strength || 10
        };
        this.creatures.push(ent);
        return ent;
    };

    render() {
        background(255, 200, 150);
        orbitControl(1, 0, 1);

        ambientLight(150);
        directionalLight(255, 255, 200, 0.5, 1, -0.5);

        // chão
        push();
        rotateX(HALF_PI);
        noStroke();
        fill(80, 120, 80);
        plane(2000, 2000);
        pop();

        // atualiza física dos cubos móveis
        this.updateCubes();

        // cubos
        for (let c of this.cubes) {
            push();
            translate(c.pos.x, c.pos.y, c.pos.z);
            
            if (c.weight > 0) {
                fill(120, 80, 40);
            } else {
                fill(150, 100, 50);
            }

            if (c.texture) {
                texture(c.texture);
            }

            if (c.wireframe) {
                stroke(0);
            } else {
                noStroke();
            }

            if (c.model) {
                const b = getModelBounds(c.model);
                const s = getStretchScale(c.model, c.size);

                scale(s.x, s.y, s.z);
                scale(1, -1, 1);

                const cx = b.min.x + b.size.x / 2;
                const cy = b.min.y + b.size.y / 2;
                const cz = b.min.z + b.size.z / 2;

                translate(-cx, -cy, -cz);
                model(c.model);
                pop();
                continue;
            }

            box(c.size.x, c.size.y, c.size.z);
            pop();
        }

        // update + render creatures
        for (let ent of this.creatures) {
            this.updateCreature(ent);
            const model = this.safeModelAt(ent.state, ent.frame);
            this.drawModel(ent.position, model, ent.rotation, ent.modelScale);
        }

        // indicador do player
        push();
        const player = this.creatures[0];
        translate(player.position.x, player.position.y - player.size.y - 90, player.position.z);
        fill(255, 255, 50, 150);
        noStroke();
        rotateX(HALF_PI);
        torus(10, 3, 8, 4);
        pop();
    };

    updateCubes() {
        const dt = deltaTime / 16.666;

        for (let c of this.cubes) {
            if (c.weight <= 0) continue;

            // gravidade
            c.vel.y += this.GRAVITY * dt;
            c.pos.y += c.vel.y * dt;

            // movimento horizontal
            c.pos.x += c.vel.x * dt;
            c.pos.z += c.vel.z * dt;

            // fricção forte
            c.vel.x *= 0.7;
            c.vel.z *= 0.7;
            
            // para movimento muito pequeno
            if (Math.abs(c.vel.x) < 0.1) c.vel.x = 0;
            if (Math.abs(c.vel.z) < 0.1) c.vel.z = 0;

            // chão
            const halfY = c.size.y / 2;
            if (c.pos.y >= this.GROUND_Y - halfY) {
                c.pos.y = this.GROUND_Y - halfY;
                c.vel.y = 0;
            }

            // colisão vertical (ficar em cima)
            for (let other of this.cubes) {
                if (other === c) continue;
                
                if (this.boxesOverlapXZ(c.pos, c.size, other.pos, other.size)) {
                    const cubeTop = other.pos.y - other.size.y / 2;
                    const cubeBottom = c.pos.y + c.size.y / 2;
                    
                    if (c.vel.y >= 0 && cubeBottom >= cubeTop - 2 && cubeBottom <= cubeTop + 5) {
                        c.pos.y = cubeTop - c.size.y / 2;
                        c.vel.y = 0;
                    }
                }
            }
        }
        
        // Segunda passada: resolve colisões horizontais
        for (let c of this.cubes) {
            if (c.weight <= 0) continue;
            
            for (let other of this.cubes) {
                if (other === c) continue;
                
                if (this.boxesOverlap(c.pos, c.size, other.pos, other.size)) {
                    // verifica se NÃO está em cima
                    const cubeTop = other.pos.y - other.size.y / 2;
                    const cubeBottom = c.pos.y + c.size.y / 2;
                    const isOnTop = Math.abs(cubeBottom - cubeTop) < 4;
                    
                    if (!isOnTop) {
                        const dx = c.pos.x - other.pos.x;
                        const dz = c.pos.z - other.pos.z;
                        
                        // só empurra se este cubo está se movendo
                        const isMoving = Math.abs(c.vel.x) > 0.2 || Math.abs(c.vel.z) > 0.2;
                        
                        if (Math.abs(dx) > Math.abs(dz)) {
                            const pushDir = dx > 0 ? 1 : -1;
                            const overlap = (c.size.x / 2 + other.size.x / 2) - Math.abs(dx);
                            
                            if (other.weight > 0 && isMoving) {
                                // empurra o outro se for mais leve ou igual
                                if (c.weight >= other.weight) {
                                    other.vel.x += pushDir * 0.15;
                                    c.pos.x += pushDir * (overlap / 2);
                                    other.pos.x -= pushDir * (overlap / 2);
                                } else {
                                    c.pos.x += pushDir * overlap;
                                    c.vel.x = 0;
                                }
                            } else {
                                c.pos.x += pushDir * overlap;
                                c.vel.x = 0;
                            }
                        } else {
                            const pushDir = dz > 0 ? 1 : -1;
                            const overlap = (c.size.z / 2 + other.size.z / 2) - Math.abs(dz);
                            
                            if (other.weight > 0 && isMoving) {
                                if (c.weight >= other.weight) {
                                    other.vel.z += pushDir * 0.15;
                                    c.pos.z += pushDir * (overlap / 2);
                                    other.pos.z -= pushDir * (overlap / 2);
                                } else {
                                    c.pos.z += pushDir * overlap;
                                    c.vel.z = 0;
                                }
                            } else {
                                c.pos.z += pushDir * overlap;
                                c.vel.z = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    safeModelAt(state, frame) {
        const states = this.models.player;
        if (!states[state]) return null;
        if (!states[state][frame]) return null;
        return states[state][frame];
    };

    updateCreature(ent) {
        const dt = deltaTime / 16.666;

        // gravidade
        ent.vel.y += this.GRAVITY * dt;

        // movimento do NPC
        let moveVec = createVector(0, 0, 0);

        if (ent.npc) {
            if (ent.traveling && ent.targetPos) {
                const toTarget = p5.Vector.sub(ent.targetPos, ent.position);
                const dist = toTarget.mag();

                if (dist < 6) {
                    ent.traveling = false;
                    ent.arrivedAt = millis();
                    ent.state = 'idle';
                    ent.frame = 0;
                } else {
                    ent.state = 'run';
                    ent.dirVec = toTarget.normalize();
                    moveVec = p5.Vector.mult(ent.dirVec, ent.speed);
                }
            } else {
                ent.state = 'idle';
                ent.frame = 0;

                if (ent.arrivedAt && millis() - ent.arrivedAt > ent.respawnDelay) {
                    const base = ent.spawnPos || ent.position;
                    const newTarget = createVector(
                        base.x + random(-200, 200), 
                        base.y, 
                        base.z + random(-200, 200)
                    );
                    ent.targetPos = newTarget;
                    ent.traveling = true;
                    ent.arrivedAt = 0;
                }
            }
        } else {
            // player
            moveVec = (ent._inputMoveVec) ? ent._inputMoveVec.copy() : createVector(0, 0, 0);
            ent.state = (moveVec.mag() > 0.001) ? 'run' : 'idle';
        }

        // aplica movimento com colisão
        if (moveVec.mag() > 0.001) {
            const scaled = p5.Vector.mult(moveVec, dt);
            this.applyMovement(ent, scaled);
        }

        // aplica gravidade
        ent.position.y += ent.vel.y * dt;

        // colisão com chão
        const halfY = ent.size.y / 2;
        if (ent.position.y >= this.GROUND_Y) {
            ent.position.y = this.GROUND_Y;
            ent.vel.y = 0;
            ent.onGround = true;
        } else {
            ent.onGround = false;
        }

        // colisão com cubos (vertical)
        for (let c of this.cubes) {
            const overlapXZ = this.boxesOverlapXZ(ent.position, ent.size, c.pos, c.size);
            
            if (overlapXZ && ent.vel.y >= 0) {
                const cubeTop = c.pos.y - c.size.y / 2;
                const entBottom = ent.position.y + halfY;
                
                if (entBottom >= cubeTop - 2 && entBottom <= cubeTop + 5) {
                    ent.position.y = cubeTop - halfY;
                    ent.vel.y = 0;
                    ent.onGround = true;
                }
            }
        }

        // atualiza rotação
        const faceVec = (ent.npc) ? moveVec : (ent._inputMoveVec || moveVec);
        if (faceVec.mag() > 0.001) {
            ent.rotation = atan2(faceVec.x, faceVec.z);
        }

        // animação
        if (!ent._lastAnimTime) ent._lastAnimTime = 0;
        if (millis() - ent._lastAnimTime > this.FRAME_INTERVAL) {
            ent._lastAnimTime = millis();
            if (ent.state === "run") {
                ent.frame = (ent.frame + 1) % this.RUN_FRAMES;
            } else {
                ent.frame = 0;
            }
        }

        if (ent._inputMoveVec) delete ent._inputMoveVec;
    };

    applyMovement(ent, movement) {
        // tenta mover em X
        ent.position.x += movement.x;
        
        // verifica colisões
        let blocked = false;
        
        for (let c of this.cubes) {
            if (this.boxesOverlap(ent.position, ent.size, c.pos, c.size)) {
                // verifica se está andando em cima do cubo
                const cubeTop = c.pos.y - c.size.y / 2;
                const entBottom = ent.position.y + ent.size.y / 2;
                const isOnTop = Math.abs(entBottom - cubeTop) < 3;
                
                if (isOnTop) {
                    // está em cima, não faz nada, deixa andar
                    continue;
                }
                
                // verifica se pode subir (step up)
                const stepHeight = cubeTop - entBottom;
                
                if (stepHeight > 0 && stepHeight <= this.STEP_HEIGHT && ent.onGround) {
                    // sobe o degrau
                    ent.position.y = cubeTop - ent.size.y / 2 - 0.5;
                } else {
                    // bloqueia movimento
                    ent.position.x -= movement.x;
                    blocked = true;
                    
                    // tenta empurrar cubo (só se não estiver em cima)
                    if (c.weight > 0 && ent.strength >= c.weight && !isOnTop) {
                        c.vel.x += (movement.x > 0 ? 1 : -1) * this.PUSH_FORCE;
                    }
                }
                break;
            }
        }

        // verifica colisão com outras criaturas
        if (!blocked) {
            for (let other of this.creatures) {
                if (other === ent) continue;
                
                if (this.boxesOverlap(ent.position, ent.size, other.position, other.size)) {
                    ent.position.x -= movement.x;
                    break;
                }
            }
        }

        // tenta mover em Z
        ent.position.z += movement.z;
        blocked = false;
        
        for (let c of this.cubes) {
            if (this.boxesOverlap(ent.position, ent.size, c.pos, c.size)) {
                // verifica se está andando em cima do cubo
                const cubeTop = c.pos.y - c.size.y / 2;
                const entBottom = ent.position.y + ent.size.y / 2;
                const isOnTop = Math.abs(entBottom - cubeTop) < 3;
                
                if (isOnTop) {
                    // está em cima, não faz nada, deixa andar
                    continue;
                }
                
                // verifica se pode subir (step up)
                const stepHeight = cubeTop - entBottom;
                
                if (stepHeight > 0 && stepHeight <= this.STEP_HEIGHT && ent.onGround) {
                    ent.position.y = cubeTop - ent.size.y / 2 - 0.5;
                } else {
                    ent.position.z -= movement.z;
                    blocked = true;
                    
                    // tenta empurrar cubo (só se não estiver em cima)
                    if (c.weight > 0 && ent.strength >= c.weight && !isOnTop) {
                        c.vel.z += (movement.z > 0 ? 1 : -1) * this.PUSH_FORCE;
                    }
                }
                break;
            }
        }

        if (!blocked) {
            for (let other of this.creatures) {
                if (other === ent) continue;
                
                if (this.boxesOverlap(ent.position, ent.size, other.position, other.size)) {
                    ent.position.z -= movement.z;
                    break;
                }
            }
        }
    };

    boxesOverlap(pos1, size1, pos2, size2) {
        return !(
            pos1.x - size1.x/2 > pos2.x + size2.x/2 ||
            pos1.x + size1.x/2 < pos2.x - size2.x/2 ||
            pos1.y - size1.y/2 > pos2.y + size2.y/2 ||
            pos1.y + size1.y/2 < pos2.y - size2.y/2 ||
            pos1.z - size1.z/2 > pos2.z + size2.z/2 ||
            pos1.z + size1.z/2 < pos2.z - size2.z/2
        );
    }

    boxesOverlapXZ(pos1, size1, pos2, size2) {
        return !(
            pos1.x - size1.x/2 > pos2.x + size2.x/2 ||
            pos1.x + size1.x/2 < pos2.x - size2.x/2 ||
            pos1.z - size1.z/2 > pos2.z + size2.z/2 ||
            pos1.z + size1.z/2 < pos2.z - size2.z/2
        );
    }

    collides3D(pos, size) {
        for (let c of this.cubes) {
            if (this.boxesOverlap(pos, size, c.pos, c.size)) {
                return true;
            }
        }
        return false;
    };

    drawModel(pos, modelModel, rotation, modelScale) {
        push();
        translate(pos.x, pos.y, pos.z);
        rotateY(rotation);

        const normalizedScale = this.getNormalizedScale(modelModel) * modelScale;
        scale(normalizedScale * 100);
        scale(1, -1, 1);
        translate(0, 60, 0);
        noStroke();

        if (modelModel) {
            model(modelModel);
        } else {
            fill(100, 150, 255);
            box(40, 80, 20);
        }

        pop();
    };

    getNormalizedScale(model) {
        if (!model) return 1;

        const modelKey = this.getModelKey(model);
        if (this.modelBounds[modelKey]) {
            return this.modelBounds[modelKey];
        }

        let minY = Infinity, maxY = -Infinity;

        if (model.vertices) {
            for (let v of model.vertices) {
                if (v.y < minY) minY = v.y;
                if (v.y > maxY) maxY = v.y;
            }

            const height = maxY - minY;
            if (height > 0) {
                const normalizedScale = 2 / height;
                this.modelBounds[modelKey] = normalizedScale;
                return normalizedScale;
            }
        }

        this.modelBounds[modelKey] = 1;
        return 1;
    };

    getModelKey(model) {
        if (model && model.vertices) {
            return `model_${model.vertices.length}`;
        }
        return 'unknown';
    };

    cameraRelativeMovement() {
        const cam = _renderer._curCamera;
        let forward = createVector(cam.centerX - cam.eyeX, 0, cam.centerZ - cam.eyeZ);
        if (forward.mag() === 0) forward = createVector(0, 0, 1);
        forward.normalize();
        let right = createVector(forward.z, 0, -forward.x);

        const speed = 3;
        let mv = createVector(0, 0, 0);

        if (keyIsDown(87) || keyIsDown(UP_ARROW)) {
            mv.add(p5.Vector.mult(forward, speed));
        }
        if (keyIsDown(83) || keyIsDown(DOWN_ARROW)) {
            mv.sub(p5.Vector.mult(forward, speed));
        }
        if (keyIsDown(68) || keyIsDown(RIGHT_ARROW)) {
            mv.sub(p5.Vector.mult(right, speed));
        }
        if (keyIsDown(65) || keyIsDown(LEFT_ARROW)) {
            mv.add(p5.Vector.mult(right, speed));
        }

        return mv;
    };

    jump(ent) {
        if (ent.onGround) {
            ent.vel.y = -15;
            ent.onGround = false;
        }
    };
}