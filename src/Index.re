open Webapi.Dom;

let documentEventTarget =
  document
  |> Document.asHtmlDocument
  |> Ext.Option.andThen(HtmlDocument.body)
  |> Ext.Option.unsafelyUnwrapOption
  |> Element.asEventTarget;

let initialSnake = Snake.create([(10, 10), (11, 10), (12, 10), (13, 10)]);

let initialFood = Food.create((15, 10));

let initialDirection = Direction.Right;

let initialWorld = World.create(initialSnake, initialFood, initialDirection);

let state = ref(initialWorld);

let updateState = (gameOver, newWorld) =>
  if (gameOver == false) {
    Draw.clearScene();
    Draw.drawSnake(World.snake(newWorld));
    Draw.drawFood(World.food(newWorld));
    newWorld;
  } else {
    Draw.drawWord("Lets Start Again");
    /* To DO: Add Game Over message and reload */
    initialWorld;
  };

let handleTick = () => {
  let oldWorld = state^;
  let food = Snake.checkFood(World.snake(oldWorld), World.food(oldWorld));
  let newWorld =
    World.create(
      Snake.move(
        World.snake(oldWorld),
        World.food(oldWorld),
        World.direction(state^),
      ),
      food,
      World.direction(state^),
    );
  let gameOver =
    Status.checkBoundary(Snake.checkHit(World.snake(newWorld)));
  state := updateState(gameOver, newWorld);
};

Js.Global.setInterval(handleTick, 300);

let changeDirection = evt =>
  switch (Key.parseKey(evt), World.direction(state^)) {
  | (ArrowUp, Direction.Down)
  | (ArrowDown, Direction.Up)
  | (ArrowRight, Direction.Left)
  | (ArrowLeft, Direction.Right) => World.direction(state^)
  | (ArrowUp, _) => Direction.Up
  | (ArrowDown, _) => Direction.Down
  | (ArrowLeft, _) => Direction.Left
  | (ArrowRight, _) => Direction.Right
  | (_, _) => World.direction(state^)
  };

let handleEvent = evt => {
  let oldWorld = state^;
  let food = Snake.checkFood(World.snake(oldWorld), World.food(oldWorld));
  let newWorld =
    World.create(
      Snake.move(
        World.snake(oldWorld),
        World.food(oldWorld),
        changeDirection(evt),
      ),
      food,
      changeDirection(evt),
    );
  let gameOver =
    Status.checkBoundary(Snake.checkHit(World.snake(newWorld)));
  state := updateState(gameOver, newWorld);
};

Webapi.Dom.EventTarget.addKeyDownEventListener(
  handleEvent,
  documentEventTarget,
);