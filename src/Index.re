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

let randomFood = Food.create((15, 12));

let handleTick = () => {
  let oldWorld = state^;
  let head = List.hd([World.snake(state^)]);
  let food = World.food(oldWorld);
  let foodStatus =
    if (Food.at(head, food) == true) {
      randomFood;
    } else {
      World.food(oldWorld);
    };
  let newWorld =
    World.create(
      Snake.move(
        World.snake(oldWorld),
        World.food(foodStatus),
        World.direction(state^),
      ),
      World.food(oldWorld),
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
  Js.log(changeDirection(evt));
  state := newWorld;
  Js.log(state^);
};

Webapi.Dom.EventTarget.addKeyDownEventListener(
  handleEvent,
  documentEventTarget,
);