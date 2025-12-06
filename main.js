import { World } from './world.js';
let world;

function preload() {
    world = new World();

    world.models.player.idle = [];
    world.models.player.idle[0] = safeLoadModel(`data/player/idle/0.obj`);

    world.models.player.run = [];
    for (let f = 0; f < world.RUN_FRAMES; f++) {
        world.models.player.run[f] = safeLoadModel(`data/player/run/${f}.obj`);
    }

    world.models.player.use = [];
    for (let f = 0; f < world.USE_FRAMES; f++) {
        world.models.player.use[f] = safeLoadModel(`data/player/use/${f}.obj`);
    }

    // Carregar modelo da torre
    //world.models.tower = safeLoadModel(`data/structure/wooden watch tower2.obj`);
}

function safeLoadModel(path) {
    let mdl = null;
    try {
        mdl = loadModel(path, true,
            () => { console.log('Modelo carregado:', path); },
            () => { console.log('Erro ao carregar:', path); }
        );
    } catch (e) {
        console.log('Exceção ao carregar modelo:', path, e);
    }
    return mdl;
}


function setup() {
    createCanvas(800, 600, WEBGL);

    // posicionamento inicial da câmera: eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ
    camera(100, -500, 900,   // posição da câmera (eye)
           0, 0, 0,     // centro/target da câmera (center) -> centerX = 100 aqui
           0, 1, 0);      // vetor "up"

    world.new_cube(createVector(-320, -40, 160), createVector(100, 120, 100), 2);
    world.new_cube(createVector(-320, -400, 160), createVector(100, 120, 100), 2);
    world.new_cube(createVector(0, -40, 480), createVector(60, 60, 60));
    const cubes = []; // registra todos os AABBs criados

    function spawnCube(pos, size, type = 1) {
        const half = p5.Vector.mult(size, 0.5);
        const aabb = {
            min: createVector(pos.x - half.x, pos.y - half.y, pos.z - half.z),
            max: createVector(pos.x + half.x, pos.y + half.y, pos.z + half.z)
        };

        // checa overlap com todos os existentes
        for (let c of cubes) {
            if (
                aabb.min.x <= c.max.x && aabb.max.x >= c.min.x &&
                aabb.min.y <= c.max.y && aabb.max.y >= c.min.y &&
                aabb.min.z <= c.max.z && aabb.max.z >= c.min.z
            ) {
                return false; // bateu → descarta
            }
        }

        cubes.push(aabb);
        world.new_cube(pos, size, type);
        return true;
    }

    // seed inicial
    spawnCube(createVector(-320, -40, 160), createVector(100, 120, 100), 2);
    spawnCube(createVector(-320, -400, 160), createVector(100, 120, 100), 2);
    spawnCube(createVector(0, -40, 480), createVector(60, 60, 60), 1);

    // spam controlado de cubos (centenas, zero interpenetração)
    for (let i = 0; i < 1000; i++) {
        let tries = 0;
        while (tries < 50) {
            const pos = createVector(
                random(-1000, 1000),
                random(-1000, 1000),
                random(-1000, 1000)
            );

            const size = createVector(
                random(40, 50),
                random(40, 50),
                random(40, 50)
            );

            if (spawnCube(pos, size, 1)) break; // aprovado
            tries++;
        }
    }

    world.new_cube(createVector(400, -400, 0), createVector(120, 400, 120), 2, loadImage('data/test.png'), loadModel('data/structure/wooden watch tower2.obj'), false, 50);

    world.new_creature({
        position: createVector(0, -40, 0),
        state: "idle",
        npc: false,
        modelScale: 1
    });

    for (let i = 0; i < 3; i++) {
        const spawn = createVector(random(-200, 200), -40, random(-200, 200));
        const target = createVector(random(-200, 200), -40, random(-200, 200));
        const dir = p5.Vector.sub(target, spawn).normalize();
        world.new_creature({
            position: spawn,
            npc: true,
            traveling: true,
            dirVec: dir,
            speed: 1.2,
            targetPos: target,
            modelScale: 1
        });
    }
}

function draw() {
    if (world.creatures.length > 0) {
        const player = world.creatures[0];
        const movement = world.cameraRelativeMovement();
        if (movement.mag() > 0.001) {
            player._inputMoveVec = movement.copy();
            player.state = "run";
        } else {
            player.state = "idle";
            player.frame = 0;
            if (player._inputMoveVec) delete player._inputMoveVec;
        }

        // Pulo
        if (keyIsDown(32)) {
            world.jump(player);
        }
    }

    world.render();
}

// a gente precisa disso aqui pq o p5.js não expõe as funções globais em módulos
window.preload = preload;
window.setup = setup;
window.draw = draw;