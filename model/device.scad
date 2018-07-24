include <./hexButton.scad>
include <ComplexObjects.scad>
// Box, or case, dimensions
box_w = 95;
box_l = 100;
box_h = 20;
// Screen dimensions (screen only, not entire "hat" as well
// Hat dimensions are 85mm x 56mm
s_l = 38.192;
s_w = 57.288;
// s_l = 56;
// s_w = 85;
s_h = 20;

offset_top = 5;
// button diameter
b_d = 8;
// skrrrrrt
button_skirt = 1;
hb_sep = 2;

// The actual model
boxWithScreen();

color("red") {
    translate([20, 10, box_h - 1]) {
        honeycomb();
    }
}

color("purple") {

}

// Here there be modules

module boxWithScreen() {
    difference() {
        translate([0, 0, box_h]) rotate([-90,0,0])
            roundedRect(box_w, box_h, box_l / 2, r = 4);
        translate([(box_w - s_w) / 2, box_l - s_l - offset_top, 5])
            cube([s_w, s_l ,box_h]);
    }
}

module honeycomb() {
    translate([0, 3, 0]) {
        hexButton(b_d, button_skirt);
        translate([0, b_d + hb_sep, 0])
            hexButton(b_d, button_skirt);
        translate([b_d + 1, 5, 0])
            hexButton(b_d, button_skirt);
        translate([b_d + 1, 15, 0])
            hexButton(b_d, button_skirt);
        translate([b_d + 1, -5, 0])
            hexButton(b_d, button_skirt);
        translate([b_d * 2 + hb_sep, 0, 0])
            hexButton(b_d, button_skirt);
        translate([b_d * 2 + hb_sep, b_d + hb_sep , 0])
            hexButton(b_d, button_skirt);
    }
}
