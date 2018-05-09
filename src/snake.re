type t = list(Cell.t);

let move = (snake, food, direction) => {
  let head = List.hd(snake);
  let newHead =
    switch (direction) {
    | Direction.Up => Cell.create((Cell.x(head), Cell.y(head) - 1))
    | Direction.Down => Cell.create((Cell.x(head), Cell.y(head) + 1))
    | Direction.Left => Cell.create((Cell.x(head) - 1, Cell.y(head)))
    | Direction.Right => Cell.create((Cell.x(head) + 1, Cell.y(head)))
    };
  let newTail =
    if (Food.at(newHead, food) == true) {
      snake;
    } else {
      snake |> List.rev |> List.tl |> List.rev;
    };
  [newHead] @ newTail;
};

let randomelement = l => List.nth(l, Random.int(List.length(l)));

let randNum = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21];

let checkFood = (snake, food) => {
  let head = List.hd(snake);
  let foodPosition =
    if (Food.at(head, food) == true) {
      Food.create((randomelement(randNum), randomelement(randNum)));
    } else {
      food;
    };
  foodPosition;
};

let checkHit = snake => {
  let head = List.hd(snake);
  head;
};

let create = xs => List.map(Cell.create, xs);

let body = t => t;