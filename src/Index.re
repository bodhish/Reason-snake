open Webapi.Dom;

open Webapi.Canvas;

let map = f =>
  fun
  | Some(v) => Some(f(v))
  | None => None;

let unsafelyUnwrapOption =
  fun
  | Some(v) => v
  | None => raise(Invalid_argument("Passed `None` to unsafelyUnwrapOption"));

let canvasEl =
  Document.getElementById("snake-game", document) |> unsafelyUnwrapOption;

let ctx = CanvasElement.getContext2d(canvasEl);

let canvasWidth =
  canvasEl
  |> Element.asHtmlElement
  |> map(HtmlElement.offsetWidth)
  |> unsafelyUnwrapOption;

let canvasHeight =
  canvasEl
  |> Element.asHtmlElement
  |> map(HtmlElement.offsetHeight)
  |> unsafelyUnwrapOption;

let drawScene = ctx =>
  ctx
  |> Canvas2d.clearRect(
       ~x=0.,
       ~y=0.,
       ~w=float_of_int(canvasWidth),
       ~h=float_of_int(canvasHeight),
     );

type cell = {
  x: int,
  y: int,
};

let clearScene = ctx =>
  Canvas2d.clearRect(
    ~x=0.,
    ~y=0.,
    ~w=float_of_int(canvasWidth),
    ~h=float_of_int(canvasHeight),
    ctx,
  );

type snake = list(cell);

let drawCell = (ctx, fillColor, cell) => {
  Canvas2d.setFillStyle(ctx, String, fillColor);
  Canvas2d.setStrokeStyle(ctx, String, "white");
  ctx
  |> Canvas2d.fillRect(
       ~x=float_of_int(cell.x * 10),
       ~y=float_of_int(cell.y * 10),
       ~w=10.,
       ~h=10.,
     );
  ctx
  |> Canvas2d.strokeRect(
       ~x=float_of_int(cell.x * 10),
       ~y=float_of_int(cell.y * 10),
       ~w=10.,
       ~h=10.,
     );
};

let initialSnake = [
  {x: 10, y: 10},
  {x: 11, y: 10},
  {x: 12, y: 10},
  {x: 13, y: 10},
];

type food = cell;

type world = {
  snake,
  food,
};

let initialFood = {x: 20, y: 20};

let initialWorld = {snake: initialSnake, food: initialFood};

let snake = ref(initialWorld);

let drawSnakeCell = drawCell(ctx, "#1179BF");

let drawFoodCell = drawCell(ctx, "#af2010");

let state = ref(initialWorld);

let drawSnake = snake => List.iter(drawSnakeCell, snake);

let moveSnake = snake => List.map(cell => {x: cell.x + 1, y: cell.y}, snake);

Js.Global.setInterval(
  () => {
    let oldWorld = state^;
    let newWorld = {snake: moveSnake(oldWorld.snake), food: oldWorld.food};
    state := newWorld;
    clearScene(ctx);
    drawSnake(newWorld.snake);
    drawFoodCell(newWorld.food);
  },
  300,
);

ctx |> drawScene;