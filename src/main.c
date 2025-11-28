// tp_people.c
// gcc tp_people.c -o tp_people -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

#include "urb.h"      // tua lib de listas (urb_new, urb_push, etc)
#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct Person {
    Vector3 position;
    Vector3 velocity;
    float width;
    float height;
    float jumpForce;
    bool grounded;
} Person;

typedef struct World {
    List* hitboxes; // lista de BoundingBox* (como no teu exemplo)
    List* people;   // lista de Person*
    float gravity;
} World;

// --- utilitários ---
static inline BoundingBox PersonBox(const Person *p) {
    BoundingBox b;
    b.min = (Vector3){ p->position.x - p->width*0.5f, p->position.y,                p->position.z - p->width*0.5f };
    b.max = (Vector3){ p->position.x + p->width*0.5f, p->position.y + p->height, p->position.z + p->width*0.5f };
    return b;
}

static inline Vector3 SolvePenetration(const BoundingBox a, const BoundingBox b) {
    // calcula separação mínima para tirar A de dentro de B
    float dx1 = b.max.x - a.min.x; // penetração vindo da direita (B está à direita)
    float dx2 = a.max.x - b.min.x; // penetração vindo da esquerda
    float dz1 = b.max.z - a.min.z;
    float dz2 = a.max.z - b.min.z;
    float dy1 = b.max.y - a.min.y;
    float dy2 = a.max.y - b.min.y;

    float minPen = dx1;
    Vector3 fix = (Vector3){ dx1, 0, 0 };

    if (dx2 < minPen) { minPen = dx2; fix = (Vector3){ -dx2, 0, 0 }; }
    if (dz1 < minPen) { minPen = dz1; fix = (Vector3){ 0, 0, dz1 }; }
    if (dz2 < minPen) { minPen = dz2; fix = (Vector3){ 0, 0, -dz2 }; }
    if (dy1 < minPen) { minPen = dy1; fix = (Vector3){ 0, dy1, 0 }; }
    if (dy2 < minPen) { minPen = dy2; fix = (Vector3){ 0, -dy2, 0 }; }

    return fix;
}

int main(void) {
    InitWindow(1280, 720, "Raylib - People collisions (push) + world hitboxes");
    SetTargetFPS(60);

    // -----------------------
    // WORLD
    // -----------------------
    World world;
    world.hitboxes = urb_new(URB_DEFAULT_SIZE);
    world.people   = urb_new(URB_DEFAULT_SIZE);
    world.gravity = -20.0f;

    // cria hitboxes (usa exemplos do teu código)
    BoundingBox *chao = malloc(sizeof(BoundingBox));
    *chao = (BoundingBox){ {-10, 0, -10}, {10, 1, 10} };
    BoundingBox *caixa = malloc(sizeof(BoundingBox));
    *caixa = (BoundingBox){ {2, 0, 2}, {4, 4, 4} };
    BoundingBox *caixa2 = malloc(sizeof(BoundingBox));
    *caixa2 = (BoundingBox){ {-4, 0, 3}, {-2, 3, 5} };

    urb_push(world.hitboxes, (Value){ .p = chao });
    urb_push(world.hitboxes, (Value){ .p = caixa });
    urb_push(world.hitboxes, (Value){ .p = caixa2 });

    // -----------------------
    // PLAYER (também é uma Person e vai pra world.people)
    // -----------------------
    Person *player = malloc(sizeof(Person));
    player->position = (Vector3){ 0, 1, 0 };
    player->velocity = (Vector3){ 0, 0, 0 };
    player->width = 1.0f;
    player->height = 2.0f;
    player->jumpForce = 10.0f;
    player->grounded = false;
    urb_push(world.people, (Value){ .p = player });

    // Spawn alguns NPCs
    for (int i = 0; i < 6; i++) {
        Person *npc = malloc(sizeof(Person));
        npc->position = (Vector3){ -6.0f + i*2.0f, 1.0f, 6.0f }; // em linha
        npc->velocity = (Vector3){ 0, 0, 0 };
        npc->width = 1.0f;
        npc->height = 2.0f;
        npc->jumpForce = 0.0f;
        npc->grounded = false;
        urb_push(world.people, (Value){ .p = npc });
    }

	player = world.people->data[4].p;

    // -----------------------
    // CAMERA ORBIT (usa posição do player[0])
    // -----------------------
    float yaw = 0.0f;
    float pitch = 0.35f;
    float distance = 8.0f;
    Camera cam = {0};
    cam.up = (Vector3){ 0, 1, 0 };
    cam.fovy = 45.0f;

    Vector2 lastMouse = GetMousePosition();
    bool dragging = false;

    // movimento do player
    const float speed = 8.0f;
    // damping para evitar acúmulo de velocidade horizontal nos NPCs
    const float damping = 8.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // ----- ZOOM
        distance -= GetMouseWheelMove() * 0.8f;
        if (distance < 2.0f) distance = 2.0f;
        if (distance > 20.0f) distance = 20.0f;

        // ----- ORBIT
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (dragging) {
                Vector2 d = { m.x - lastMouse.x, m.y - lastMouse.y };
                yaw   -= d.x * 0.004f;
                pitch -= d.y * 0.004f;
                if (pitch < 0.05f) pitch = 0.05f;
                if (pitch > 1.3f) pitch = 1.3f;
            }
            lastMouse = m;
            dragging = true;
        } else dragging = false;

        // ----- INPUT DO PLAYER (index 0 na lista)
        // calcula vetores relativos à câmera
        Vector3 forward = { sinf(yaw), 0, cosf(yaw) };
        Vector3 right   = { forward.z, 0, -forward.x };

        // pega o player (assumimos que está em data[0])
        if (world.people->size == 0) break;
        Person *pplayer = (Person*)world.people->data[0].p;

        Vector3 input = {0,0,0};
        if (IsKeyDown(KEY_W)) { input.x -= forward.x; input.z -= forward.z; }
        if (IsKeyDown(KEY_S)) { input.x += forward.x; input.z += forward.z; }
        if (IsKeyDown(KEY_A)) { input.x -= right.x;   input.z -= right.z;   }
        if (IsKeyDown(KEY_D)) { input.x += right.x;   input.z += right.z;   }

        float ilen = input.x*input.x + input.z*input.z;
        if (ilen > 0.0001f) {
            float inv = 1.0f / sqrtf(ilen);
            // set velocity horizontal diretamente (override), mantém y intacto
            pplayer->velocity.x = input.x * inv * speed;
            pplayer->velocity.z = input.z * inv * speed;
        } else {
            // desacelera horizontal quando sem input (simples friction)
            pplayer->velocity.x = pplayer->velocity.x * (1.0f - fminf(damping*dt, 1.0f));
            pplayer->velocity.z = pplayer->velocity.z * (1.0f - fminf(damping*dt, 1.0f));
        }

        // pulo
        if (pplayer->grounded && IsKeyPressed(KEY_SPACE)) {
            pplayer->velocity.y = pplayer->jumpForce;
            pplayer->grounded = false;
        }

        // ----- FÍSICA: aplicar gravidade + integrar movimento para todas as pessoas
        for (int i = 0; i < world.people->size; i++) {
            Person *pp = (Person*)world.people->data[i].p;
            // gravidade
            pp->velocity.y += world.gravity * dt;

            // integra posição
            pp->position.x += pp->velocity.x * dt;
            pp->position.z += pp->velocity.z * dt;
            pp->position.y += pp->velocity.y * dt;

            // reset grounded, será recalculado nas colisões
            pp->grounded = false;
        }

        // calcula câmera em cima do player atualizado
        cam.position = (Vector3){
            pplayer->position.x + sinf(yaw) * distance * cosf(pitch),
            pplayer->position.y + distance * sinf(pitch),
            pplayer->position.z + cosf(yaw) * distance * cosf(pitch)
        };
        cam.target = (Vector3){ pplayer->position.x, pplayer->position.y + 1.0f, pplayer->position.z };

        // ----- COLISÃO: pessoas -> hitboxes (mapa)
        for (int i = 0; i < world.people->size; i++) {
            Person *pp = (Person*)world.people->data[i].p;
            BoundingBox pb = PersonBox(pp);

            for (int h = 0; h < world.hitboxes->size; h++) {
                BoundingBox hb = *(BoundingBox*)world.hitboxes->data[h].p;
                if (!CheckCollisionBoxes(pb, hb)) continue;

                Vector3 fix = SolvePenetration(pb, hb);

                pp->position.x += fix.x;
                pp->position.y += fix.y;
                pp->position.z += fix.z;

                // se correção vertical para cima -> grounded
                if (fix.y > 0.0f) {
                    pp->grounded = true;
                    pp->velocity.y = 0.0f;
                }
                if (fix.y < 0.0f) {
                    // colidiu por cima (teto) -> zera y
                    pp->velocity.y = 0.0f;
                }

                // atualizar bounding box para próximas checagens
                pb = PersonBox(pp);
            }
        }

        // ----- COLISÃO: pessoa <-> pessoa (empurrão mútuo 50/50)
        // iterar pares (i < j)
        for (int i = 0; i < world.people->size; i++) {
            Person *a = (Person*)world.people->data[i].p;
            BoundingBox boxA = PersonBox(a);

            for (int j = i + 1; j < world.people->size; j++) {
                Person *b = (Person*)world.people->data[j].p;
                BoundingBox boxB = PersonBox(b);

                if (!CheckCollisionBoxes(boxA, boxB)) continue;

                Vector3 fix = SolvePenetration(boxA, boxB);

                // separação mutua 50/50
                a->position.x += fix.x * 0.5f;
                a->position.y += fix.y * 0.5f;
                a->position.z += fix.z * 0.5f;

                b->position.x -= fix.x * 0.5f;
                b->position.y -= fix.y * 0.5f;
                b->position.z -= fix.z * 0.5f;

                // ajustar velocidades para evitar "grudar"
                // projeta componente horizontal do fix como impulso oposto nas velocities
                // distribuição simples: metade do deslocamento em velocidade instantânea inversa
                if (fabsf(fix.x) > 0.0001f) {
                    float push = (fix.x * 0.5f) / fmaxf(0.02f, dt); // evita dividir por zero
                    a->velocity.x += push * 0.5f;
                    b->velocity.x -= push * 0.5f;
                }
                if (fabsf(fix.z) > 0.0001f) {
                    float push = (fix.z * 0.5f) / fmaxf(0.02f, dt);
                    a->velocity.z += push * 0.5f;
                    b->velocity.z -= push * 0.5f;
                }

                // se correção vertical positiva: quem recebeu correção para cima está grounded
                if (fix.y > 0.0f) {
                    a->grounded = true;
                    a->velocity.y = 0.0f;
                }
                if (fix.y < 0.0f) {
                    b->grounded = true;
                    b->velocity.y = 0.0f;
                }

                // atualizar caixas locais
                boxA = PersonBox(a);
                boxB = PersonBox(b);
            }
        }

        // ----- DRAW
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(cam);
                DrawGrid(40, 1.0f);

                // desenha hitboxes (mapa)
                for (int i = 0; i < world.hitboxes->size; i++) {
                    BoundingBox box = *(BoundingBox*)world.hitboxes->data[i].p;
                    Vector3 size = { box.max.x - box.min.x, box.max.y - box.min.y, box.max.z - box.min.z };
                    Vector3 pos = { (box.min.x + box.max.x)/2.0f, (box.min.y + box.max.y)/2.0f, (box.min.z + box.max.z)/2.0f };
                    DrawCube(pos, size.x, size.y, size.z, LIGHTGRAY);
                    DrawCubeWires(pos, size.x, size.y, size.z, DARKGRAY);
                }

                // desenha people
                for (int i = 0; i < world.people->size; i++) {
                    Person *pp = (Person*)world.people->data[i].p;
                    Vector3 drawPos = { pp->position.x, pp->position.y + pp->height * 0.5f, pp->position.z };
                    Color col = (i == 0) ? RED : BLUE;
                    DrawCube(drawPos, pp->width, pp->height, pp->width, col);
                    DrawCubeWires(drawPos, pp->width, pp->height, pp->width, BLACK);
                }

                // desenha posição da camera para debug
                DrawSphere(cam.position, 0.12f, GREEN);

            EndMode3D();

            // HUD
            DrawText(pplayer->grounded ? "PLAYER: GROUND = YES" : "PLAYER: GROUND = NO", 20, 20, 20, DARKGRAY);
            DrawText("WASD move | SPACE jump | Right click + drag to orbit | Mouse wheel zoom", 20, 44, 16, DARKGRAY);
            DrawFPS(10, 700);
        EndDrawing();
    }

    // liberar memória (simples)
    for (int i = 0; i < world.hitboxes->size; i++) free(world.hitboxes->data[i].p);
    for (int i = 0; i < world.people->size; i++) free(world.people->data[i].p);
    // supondo que urb tem função de free, caso não tenha, apenas não faz nada
    // urb_free(world.hitboxes);
    // urb_free(world.people);

    CloseWindow();
    return 0;
}
