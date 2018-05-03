type t = Cell.t;

let create = Cell.create;

let position = t => t;

let at = (cell: Cell.t, food: t) : bool => cell == food;