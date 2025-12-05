

export class World {
    constructor()
    {
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
        this.COLLISION_MARGIN = 2;
        this.STEP_HEIGHT = 20;
    }

    new_cube(pos, size) {
        this.cubes.push({ pos, size });
    };

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
            onGround: true,
            _lastAnimTime: millis()
        };
        this.creatures.push(ent);
        return ent;
    };

    render() {
        background(255,200,150);
        // as opções do orbitControl são: sensitivityX, sensitivityY, zoomSensitivity
        // é pra a gente nao ver debaixo do chão

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

        // cubos
        for (let c of this.cubes) {
            push();
            translate(c.pos.x, c.pos.y, c.pos.z);
            fill(150, 100, 50);
            noStroke();
            box(c.size.x, c.size.y, c.size.z);
            pop();
        }

        // update + render creatures
        for (let ent of this.creatures) {
            this.updateCreature(ent);
            const model = this.safeModelAt(ent.state, ent.frame);
            this.drawModel(ent.position, model, ent.rotation, ent.modelScale);
        }
    };

    // ---------------------------
    // Internals
    // ---------------------------
    safeModelAt(state, frame) {
        const states = this.models.player;
        if (!states[state]) return null;
        if (!states[state][frame]) return null;
        return states[state][frame];
    };

    updateCreature(ent) {
        // gravidade
        ent.vel.y += this.GRAVITY * (deltaTime / 16.666);
        ent.position.y += ent.vel.y * (deltaTime / 16.666);

        // usa movimento externo
        let moveVec = (ent._inputMoveVec) ? ent._inputMoveVec.copy() : createVector(0, 0, 0);

        // NPC movimentação
        if (ent.npc) {
            if (ent.traveling) {
                ent.state = 'run';
                const mv = p5.Vector.mult(ent.dirVec, ent.speed * (deltaTime / 16.666));
                ent.position.add(mv);
                moveVec = ent.dirVec.copy();

                if (ent.targetPos && p5.Vector.sub(ent.targetPos, ent.position).mag() < 6) {
                    ent.traveling = false;
                    ent.arrivedAt = millis();
                    ent.state = 'idle';
                    ent.frame = 0;
                }
            } else {
                ent.state = 'idle';
                ent.frame = 0;

                if (ent.arrivedAt && millis() - ent.arrivedAt > ent.respawnDelay) {
                    const base = (ent.spawnPos) ? ent.spawnPos.copy() : ent.position.copy();
                    const newTarget = createVector(base.x + random(-200, 200), base.y, base.z + random(-200, 200));
                    ent.targetPos = newTarget;
                    ent.dirVec = p5.Vector.sub(ent.targetPos, ent.position).normalize();
                    ent.traveling = true;
                    ent.arrivedAt = 0;
                    ent.state = 'run';
                }
            }
        } else {
            // jogador: aplica movimento com colisão
            if (moveVec && moveVec.mag() > 0.001) {
                ent.state = 'run';
                const scaled = p5.Vector.mult(moveVec, (deltaTime / 16.666));
                this.resolveMovementCollision(ent, scaled);
            } else {
                ent.state = 'idle';
            }
        }

        // resolve colisões verticais (gravidade + chão)
        this.resolveVerticalCollision(ent);

        // atualiza rotação
        if ((ent.npc && moveVec.mag() > 0.001) || (ent._inputMoveVec && ent._inputMoveVec.mag() > 0.001)) {
            const faceVec = (ent.npc) ? moveVec.copy() : ent._inputMoveVec.copy();
            if (faceVec.mag() > 0.001) {
                ent.rotation = atan2(faceVec.x, faceVec.z);
            }
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

    resolveMovementCollision(ent, movement) {
        // Tenta mover nos 3 eixos separadamente para deslizamento

        // X
        const nextX = p5.Vector.add(ent.position, createVector(movement.x, 0, 0));
        if (!this.collides3D(nextX, ent.size)) {
            ent.position = nextX;
        }

        // Z
        const nextZ = p5.Vector.add(ent.position, createVector(0, 0, movement.z));
        if (!this.collides3D(nextZ, ent.size)) {
            ent.position = nextZ;
        }
    };

    getAABB(pos, size) {
        const half = { x: size.x / 2, y: size.y / 2, z: size.z / 2 };
        return {
            minX: pos.x - half.x,
            maxX: pos.x + half.x,
            minY: pos.y - half.y,
            maxY: pos.y + half.y,
            minZ: pos.z - half.z,
            maxZ: pos.z + half.z
        };
    };

    checkAABBCollision(aabb1, aabb2) {
        return !(aabb1.maxX < aabb2.minX + this.COLLISION_MARGIN ||
            aabb1.minX > aabb2.maxX - this.COLLISION_MARGIN ||
            aabb1.maxY < aabb2.minY + this.COLLISION_MARGIN ||
            aabb1.minY > aabb2.maxY - this.COLLISION_MARGIN ||
            aabb1.maxZ < aabb2.minZ + this.COLLISION_MARGIN ||
            aabb1.minZ > aabb2.maxZ - this.COLLISION_MARGIN);
    };

    collides3D(pos, size) {
        const aabb = this.getAABB(pos, size);
        for (let c of this.cubes) {
            const cubeAABB = this.getAABB(c.pos, c.size);
            if (this.checkAABBCollision(aabb, cubeAABB)) {
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

        if (keyIsDown(87) || keyIsDown(UP_ARROW)) 
        {
            mv.add(p5.Vector.mult(forward, speed));
            camera(cam.eyeX + forward.x * speed, cam.eyeY, cam.eyeZ + forward.z * speed,
                   cam.centerX + forward.x * speed, cam.centerY, cam.centerZ + forward.z * speed,
                   0, 1, 0);
        }
        if (keyIsDown(83) || keyIsDown(DOWN_ARROW)) 
        {
            
            mv.sub(p5.Vector.mult(forward, speed));
            camera(cam.eyeX - forward.x * speed, cam.eyeY, cam.eyeZ - forward.z * speed,
                   cam.centerX - forward.x * speed, cam.centerY, cam.centerZ - forward.z * speed,
                   0, 1, 0);
        }
        if (keyIsDown(68) || keyIsDown(RIGHT_ARROW)) 
        {
            mv.sub(p5.Vector.mult(right, speed));
            camera(cam.eyeX - right.x * speed, cam.eyeY, cam.eyeZ - right.z * speed,
                   cam.centerX - right.x * speed, cam.centerY, cam.centerZ - right.z * speed,
                   0, 1, 0);
        }
        if (keyIsDown(65) || keyIsDown(LEFT_ARROW))
        {
            mv.add(p5.Vector.mult(right, speed));
            camera(cam.eyeX + right.x * speed, cam.eyeY, cam.eyeZ + right.z * speed,
                   cam.centerX + right.x * speed, cam.centerY, cam.centerZ + right.z * speed,
                   0, 1, 0);
        }

        return mv;
    };

    jump(ent) {
        if (ent.onGround) {
            ent.vel.y = -15;
            ent.onGround = false;
        }
    };

    resolveVerticalCollision(ent) {
        let bestSurface = null;
        for (let c of this.cubes) {
            const halfC = { x: c.size.x / 2, y: c.size.y / 2, z: c.size.z / 2 };
            const halfE = { x: ent.size.x / 2, z: ent.size.z / 2 };

            if (ent.position.x + halfE.x > c.pos.x - halfC.x &&
                ent.position.x - halfE.x < c.pos.x + halfC.x &&
                ent.position.z + halfE.z > c.pos.z - halfC.z &&
                ent.position.z - halfE.z < c.pos.z + halfC.z) {

                const surfaceY = c.pos.y - halfC.y - ent.size.y / 2;
                if (surfaceY <= ent.position.y) {
                    if (bestSurface === null || surfaceY > bestSurface) {
                        bestSurface = surfaceY;
                    }
                }
            }
        }

        if (bestSurface !== null) {
            ent.position.y = bestSurface;
            ent.vel.y = 0;
            ent.onGround = true;
            return;
        }

        if (ent.position.y >= this.GROUND_Y) {
            ent.position.y = this.GROUND_Y;
            ent.vel.y = 0;
            ent.onGround = true;
        } else {
            ent.onGround = false;
        }
    }
}