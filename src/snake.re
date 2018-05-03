type t = list(Cell.t);

let move = (t, direction) =>
  List.map(cell => Cell.create((Cell.x(cell) + 1, Cell.y(cell))), t);

let create = xs => List.map(Cell.create, xs);

let body = t => t;