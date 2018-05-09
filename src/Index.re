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

let handleTick = () => {
  let oldWorld = state^;
  let food = Snake.checkFood(World.snake(oldWorld), World.food(oldWorld));
  let gameOver =
    Status.checkBoundary(Snake.checkHit(World.snake(oldWorld)));
  let updateState =
    if (gameOver == false) {
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
    } else {
      state := oldWorld;
    };
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