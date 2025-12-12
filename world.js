import {vocabulario} from './vocabulario.js';

export class Behaviour {
    constructor(name, callback, ...args) {
        this.name = name;
        this.callback = callback;
        this.args = [...args];
        this.automatic = false;
        this.cooldown = 0;
        this.counter = 0;
        this.active = true;
    }
    run() {
        if (!this.active || this.cooldown > 0) {
            if (this.cooldown > 0) this.cooldown--;
            return;
        }
        this.callback.apply(this, this.args);
        this.counter++;
    }
}

export class Room {
    constructor(name, width, height) {
        this.name = name;
        this.size = { x: width, y: height };
        this.owner = -1;
        this.events = [];
        this.occupants = [];
    }
    addOccupant(creatureId) {
        if (!this.occupants.includes(creatureId)) this.occupants.push(creatureId);
    }
    removeOccupant(creatureId) {
        this.occupants = this.occupants.filter(id => id !== creatureId);
    }
    getRandomPosition() {
        return {
            x: Math.floor(Math.random() * this.size.x),
            y: Math.floor(Math.random() * this.size.y)
        };
    }
}

export class Item {
    constructor(name, birth) {
        this.name = name;
        this.birth = birth;
        this.creator = -1;
        this.owner = -1;
        this.capacity = 0;
        this.inventory = [];
        this.events = [];
        this.type = 'generic';
        this.edible = false;
        this.values = { food: 0, drink: 0, energy: 0, pee: 0, poo: 0 };
        this.worldPos = { x: 0, y: 0 }; // Posição fixa no mundo
    }
}

export class Creature {
    constructor(birth) {
        this.name = generateCreatureName();
        this.alive = true;
        this.birth = birth;
        this.inventory = [];
        this.needs = { hunger: 100, thirst: 100, energy: 100, pee: 0, poo: 0 };
        this.room = -1;
        this.position = { x: 0, y: 0 };
        this.targetPosition = null;
        this.path = []; // Caminho a seguir
        this.events = [];
        this.eventQueue = []; // Fila de eventos a executar
        this._render = {
            visible: true,
            color: '#888888',
            size: 5,
            currentAnimation: 'idle',
            animations: {
                idle: { frames: 1, currentFrame: 0, models: [] },
                run: { frames: 5, currentFrame: 0, models: [] },
                use: { frames: 3, currentFrame: 0, models: [] }
            }
        }
    }

    moveTo(x, y) {
        this.position = { x: Math.round(x), y: Math.round(y) };
    }

    setTarget(x, y, world) {
        this.targetPosition = { x: Math.round(x), y: Math.round(y) };
        this.path = this.calculatePath(this.position, this.targetPosition, world);
    }

    calculatePath(start, end, world) {
        // Pathfinding grid-based (Manhattan path simples)
        const path = [];
        let currentX = Math.round(start.x);
        let currentY = Math.round(start.y);
        const endX = Math.round(end.x);
        const endY = Math.round(end.y);

        // Mover horizontal primeiro, depois vertical
        while (currentX !== endX) {
            currentX += currentX < endX ? 1 : -1;
            path.push({ x: currentX, y: currentY });
        }

        while (currentY !== endY) {
            currentY += currentY < endY ? 1 : -1;
            path.push({ x: currentX, y: currentY });
        }

        return path;
    }

    updateMovement() {
        // Move 1 tile por turno (quando world.pass() é chamado)
        if (this.path.length > 0) {
            const next = this.path.shift();
            this.position = { x: next.x, y: next.y };

            if (this.path.length === 0) {
                this.targetPosition = null;
                // Processar evento da queue quando chegar ao destino
                this.processEventQueue();
            }
        }
    }

    addToInventory(itemId) { this.inventory.push(itemId); }
    removeFromInventory(itemId) {
        this.inventory = this.inventory.filter(id => id !== itemId);
    }

    queueEvent(eventName, callback, ...args) {
        this.eventQueue.push({
            name: eventName,
            callback: callback,
            args: args
        });
    }

    processEventQueue() {
        if (this.eventQueue.length > 0) {
            const event = this.eventQueue.shift();
            event.callback.apply(this, event.args);
        }
    }
}

export class World {
    constructor() {
        this.time = 0;
        this.events = [];
        this.rooms = [];
        this.items = [];
        this.creatures = [];
        this.eventLog = [];
        this.createEvent('time-tick', () => { this.time++; });
    }

    log(message, important = false) {
        this.eventLog.push({ message, important, time: this.time });
        if (this.eventLog.length > 100) this.eventLog.shift();
    }

    createEvent(name, callback, ...args) {
        const event = new Behaviour(name, callback, ...args);
        this.events.push(event);
        return this.events.length - 1;
    }

    pass() {
        for (const event of this.events) {
            if (event.active) event.run();
        }

        // Atualizar movimento de todas as criaturas
        for (const creature of this.creatures) {
            if (creature.alive) {
                creature.updateMovement();
                creature.processEventQueue();
            }
        }
    }

    spawn(type, ...args) {
        if (type === 'room') {
            const [name, width, height] = args;
            const room = new Room(name, width, height);
            this.rooms.push(room);
            return this.rooms.length - 1;
        }

        if (type === 'creature') {
            const creature = new Creature(this.time);
            this.creatures.push(creature);
            const creatureId = this.creatures.length - 1;
            this.setupCreatureEvents(creatureId);
            if (this.rooms.length > 0) {
                const roomId = Math.floor(Math.random() * this.rooms.length);
                this.moveCreatureToRoom(creatureId, roomId);
            }
            return creatureId;
        }

        if (type === 'item') {
            const [name, itemType] = args;
            const item = new Item(name || generateItemName(), this.time);
            item.type = itemType || 'generic';
            if (item.type === 'food') {
                item.edible = true;
                item.values.food = 20 + Math.floor(Math.random() * 30);
            }
            this.items.push(item);
            const itemId = this.items.length - 1;

            // Posicionar item em sala aleatória
            if (this.rooms.length > 0) {
                const roomId = Math.floor(Math.random() * this.rooms.length);
                const room = this.rooms[roomId];
                item.worldPos = {
                    x: Math.floor(Math.random() * room.size.x),
                    y: Math.floor(Math.random() * room.size.y)
                };
            }

            return itemId;
        }
    }

    setupCreatureEvents(creatureId) {
        const creature = this.creatures[creatureId];

        creature.events.push(this.createEvent(`hunger-${creatureId}`, (cId) => {
            const c = this.creatures[cId];
            if (c && c.alive) {
                c.needs.hunger = Math.max(0, c.needs.hunger - 0.5);
                if (c.needs.hunger <= 0) {
                    c.alive = false;
                    this.log(`${c.name[c.name.length - 1]} morreu de fome!`, true);
                }
            }
        }, creatureId));

        creature.events.push(this.createEvent(`thirst-${creatureId}`, (cId) => {
            const c = this.creatures[cId];
            if (c && c.alive) {
                c.needs.thirst = Math.max(0, c.needs.thirst - 0.7);
                if (c.needs.thirst <= 0) {
                    c.alive = false;
                    this.log(`${c.name[c.name.length - 1]} morreu de sede!`, true);
                }
            }
        }, creatureId));

        creature.events.push(this.createEvent(`energy-${creatureId}`, (cId) => {
            const c = this.creatures[cId];
            if (c && c.alive) c.needs.energy = Math.max(0, c.needs.energy - 0.3);
        }, creatureId));

        creature.events.push(this.createEvent(`pee-${creatureId}`, (cId) => {
            const c = this.creatures[cId];
            if (c && c.alive) c.needs.pee = Math.min(100, c.needs.pee + 0.4);
        }, creatureId));

        creature.events.push(this.createEvent(`poo-${creatureId}`, (cId) => {
            const c = this.creatures[cId];
            if (c && c.alive) c.needs.poo = Math.min(100, c.needs.poo + 0.3);
        }, creatureId));

        creature.events.push(this.createEvent(`rest-${creatureId}`, (cId) => {
            const c = this.creatures[cId];
            if (c && c.alive && c.needs.energy < 30) {
                c.needs.energy = Math.min(100, c.needs.energy + 10);
            }
        }, creatureId));
    }

    

    moveCreatureToRoom(creatureId, roomId) {
        const creature = this.creatures[creatureId];
        const newRoom = this.rooms[roomId];
        if (!creature || !newRoom) return false;
        if (creature.room !== -1 && this.rooms[creature.room]) {
            this.rooms[creature.room].removeOccupant(creatureId);
        }
        creature.room = roomId;
        creature.position = newRoom.getRandomPosition();
        newRoom.addOccupant(creatureId);
        return true;
    }
}

function generateCreatureName() {
    const nome = vocabulario.nomes[Math.floor(Math.random() * vocabulario.nomes.length)];
    const sobrenome = vocabulario.palavras[Math.floor(Math.random() * vocabulario.nomes.length)];
    return [nome, sobrenome];
}

function generateItemName() {
    const idx1 = Math.floor(Math.random() * vocabulario.palavras.length);
    let idx2 = Math.floor(Math.random() * vocabulario.palavras.length);
    while (idx2 === idx1) idx2 = Math.floor(Math.random() * vocabulario.palavras.length);
    return vocabulario.combinar(vocabulario.palavras[idx1], vocabulario.palavras[idx2], 'sobreposicao');
}