open Webapi.Canvas;

open Webapi.Dom;

let canvasEl =
  Document.getElementById("snake-game", document)
  |> Ext.Option.unsafelyUnwrapOption;

let ctx = Webapi.Canvas.CanvasElement.getContext2d(canvasEl);

let drawCell = (fillColor, cell) => {
  Canvas2d.setFillStyle(ctx, String, fillColor);
  Canvas2d.setStrokeStyle(ctx, String, "white");
  Canvas2d.fillRect(
    ~x=float_of_int(Cell.x(cell) * 10),
    ~y=float_of_int(Cell.y(cell) * 10),
    ~w=10.0,
    ~h=10.,
    ctx,
  );
  /* ctx.strokeRect(10, 10, 100, 100); */
  Canvas2d.strokeRect(
    ~x=float_of_int(Cell.x(cell) * 10),
    ~y=float_of_int(Cell.y(cell) * 10),
    ~w=10.,
    ~h=10.,
    ctx,
  );
};

let drawWord = (text: string) =>
  Canvas2d.strokeText(text, ~x=175., ~y=125., ctx);

let drawSnakeCell = cell => drawCell("#1179BF", cell);

let drawSnake = snake => List.iter(drawSnakeCell, Snake.body(snake));

let drawFoodCell = cell => drawCell("#af2010", cell);

let drawFood = food => food |> Food.position |> drawFoodCell;

let canvasWidth =
  canvasEl
  |> Element.asHtmlElement
  |> Ext.Option.map(HtmlElement.offsetWidth)
  |> Ext.Option.unsafelyUnwrapOption;

let canvasHeight =
  canvasEl
  |> Element.asHtmlElement
  |> Ext.Option.map(HtmlElement.offsetHeight)
  |> Ext.Option.unsafelyUnwrapOption;

let clearScene = () =>
  Canvas2d.clearRect(
    ~x=0.,
    ~y=0.,
    ~w=float_of_int(canvasWidth),
    ~h=float_of_int(canvasHeight),
    ctx,
  );