type t;

let create: ((int, int)) => t;

let position: t => Cell.t;

let at: (Cell.t, t) => bool;