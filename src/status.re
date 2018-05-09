let checkBoundary = hitBoundary => {
  let {Cell.x: x1, Cell.y: y1} = hitBoundary;
  let tureOrFalse =
    if (x1 == (-1) || x1 == 40) {
      Js.log("Game Over");
      true;
    } else if (y1 == (-1) || y1 == 30) {
      Js.log("Game Over");
      true;
    } else {
      false;
    };
  tureOrFalse;
};