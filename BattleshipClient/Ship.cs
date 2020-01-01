namespace BattleshipClient {

    public struct Ship {
        public enum ShipOrientation { Horizontal, Vertical }

        public int Row { get; set; }
        public int Column { get; set; }
        public int Size { get; set; }
        public ShipOrientation Orientation { get; set; }

        public static bool Overlap(Ship a, Ship b) {
            var a1 = (y: a.Row, x: a.Column);
            var a2 = a1;
            if (a.Orientation == ShipOrientation.Horizontal) a2.x += a.Size - 1;
            if (a.Orientation == ShipOrientation.Vertical) a2.y += a.Size - 1;
            var b1 = (y: b.Row, x: b.Column);
            var b2 = b1;
            if (b.Orientation == ShipOrientation.Horizontal) b2.x += b.Size - 1;
            if (b.Orientation == ShipOrientation.Vertical) b2.y += b.Size - 1;
            if (a1.x > b2.x || a2.x < b1.x) {
                return false;
            }
            if (a1.y > b2.y || a2.y < b1.y) {
                return false;
            }
            return true;
        }
    }
}
