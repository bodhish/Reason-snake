let checkBoundary = hitBoundary => {
  let {Cell.x: x1, Cell.y: y1} = hitBoundary;
  let tureOrFalse =
    if (x1 == 0 || x1 == 39) {
      Js.log("Game Over");
      true;
    } else if (y1 == 0 || y1 == 29) {
      Js.log("Game Over");
      true;
    } else {
      false;
    };
  tureOrFalse;
};