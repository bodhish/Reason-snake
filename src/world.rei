type t;

let create: (Snake.t, Food.t, Direction.t) => t;

let snake: t => Snake.t;

let food: t => Food.t;

let direction: t => Direction.t;