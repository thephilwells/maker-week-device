// Bottom width
bw = 10;
// Wall width
ww = 3;
ch = 120;
// Cup length/width
cw = 70;
difference() {
// Outer cube
cube([cw, cw, ch]);
    
// Hollowed out cube
translate([0, 0, bw])
linear_extrude(ch)
    offset(delta = -ww)
        square([cw, cw]);
}

// Good start
translate([70, 0, 0])
polyhedron(
    points=[
        [0, 0, 0], // 0
        [0, cw, 0], // 1
        [0, 0, 20], // 2
        [5, 0, 20]], // 3
    faces=[[0, 3, 2], [0, 1, 3], [3, 1, 2], [0, 2, 1]]
);

translate([70, 0, 0])
polyhedron(
    points=[
        [0, cw, 0], // 0
        [0, 0, 20], // 1
        [5, 0, 20], // 2
        [0, cw, 80], // 3
        [10, 40, 60], // 4
        [0, 0, 80]], // 5
    faces=[[5, 2, 1], [4, 0, 2], [5, 4, 2], [5, 3, 4], [3, 0, 4], [3, 5, 1, 0]]
);

