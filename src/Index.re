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

let checkBoundary = (x, y) => {
  let tureOrFalse =
    if (x == 0 || x == 39) {
      Js.log("Game Over");
      true;
    } else if (y == 0 || y == 29) {
      Js.log("Game Over");
      true;
    } else {
      false;
    };
  tureOrFalse;
};

let handleTick = () => {
  let oldWorld = state^;
  let food = Snake.checkFood(World.snake(oldWorld), World.food(oldWorld));
  let hitBound = Snake.checkHit(World.snake(oldWorld));
  Js.log(hitBound);
  let {Cell.x: x1, Cell.y: y1} = hitBound;
  Js.log(x1);
  Js.log(y1);
  let boolMon = checkBoundary(x1, y1);
  Js.log(boolMon);
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
  state := newWorld;
  Draw.clearScene();
  Draw.drawSnake(World.snake(state^));
  Draw.drawFood(World.food(state^));
};

Js.Global.setInterval(handleTick, 300);

let changeDirection = evt =>
  switch (Key.parseKey(evt)) {
  | ArrowUp => Direction.Up
  | ArrowRight => Direction.Right
  | ArrowLeft => Direction.Left
  | ArrowDown => Direction.Down
  | Ignore => World.direction(state^)
  };

let handleEvent = evt => {
  let oldWorld = state^;
  let newWorld =
    World.create(
      Snake.move(
        World.snake(oldWorld),
        World.food(oldWorld),
        changeDirection(evt),
      ),
      World.food(oldWorld),
      changeDirection(evt),
    );
  state := newWorld;
};

let gameOver = Js.log("Game Over");

Webapi.Dom.EventTarget.addKeyDownEventListener(
  handleEvent,
  documentEventTarget,
);