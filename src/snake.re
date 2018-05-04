type t = list(Cell.t);

/* Snake.create([(10, 10), (11, 10), (12, 10), (13, 10)]); */
let move = (snake, food, direction) => {
  let head = List.hd(snake);
  let newTail =
    if (Food.at(head, food) == true) {
      snake;
    } else {
      snake |> List.rev |> List.tl |> List.rev;
    };
  let newHead =
    switch (direction) {
    | Direction.Up => Cell.create((Cell.x(head), Cell.y(head) - 1))
    | Direction.Down => Cell.create((Cell.x(head), Cell.y(head) + 1))
    | Direction.Left => Cell.create((Cell.x(head) - 1, Cell.y(head)))
    | Direction.Right => Cell.create((Cell.x(head) + 1, Cell.y(head)))
    };
  [newHead] @ newTail;
};

let checkFood = (snake, food) => {
  let head = List.hd(snake);
  let foodPosition =
    if (Food.at(head, food) == true) {
      Food.create((15, 12));
    } else {
      food;
    };
  foodPosition;
};

let create = xs => List.map(Cell.create, xs);

let body = t => t;