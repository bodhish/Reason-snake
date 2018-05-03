type t = {
  canvasContext: int,
  snake: Snake.t,
  food: Food.t,
  direction: Direction.t,
};

let create = (snake, food, direction) => {
  canvasContext: 0,
  snake,
  food,
  direction,
};

let snake = t => t.snake;

let food = t => t.food;

let direction = t => t.direction;