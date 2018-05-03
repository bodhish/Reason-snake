type t =
  | ArrowUp
  | ArrowRight
  | ArrowDown
  | ArrowLeft
  | Ignore;

let parseKey = evt =>
  switch (Webapi.Dom.KeyboardEvent.key(evt)) {
  | "ArrowUp" => ArrowUp
  | "ArrowRight" => ArrowRight
  | "ArrowDown" => ArrowDown
  | "ArrowLeft" => ArrowLeft
  | _ => Ignore
  };