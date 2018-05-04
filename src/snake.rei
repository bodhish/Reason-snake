type t;

let create: list((int, int)) => t;

let move: (t, Food.t, Direction.t) => t;

let checkFood: (t, Food.t) => Food.t;

let body: t => list(Cell.t);