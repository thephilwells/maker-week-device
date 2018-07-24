include <./hexButton.scad>
include <./commandButton.scad>
include <ComplexObjects.scad>
// Box, or case, dimensions
box_w = 95;
box_l = 100;
box_h = 30;

box_thick = 5;
top_box_thick = 2;
// Screen dimensions (screen only, not entire "hat" as well
// Hat dimensions are 85mm x 56mm
s_l = 38.192;
s_w = 57.288;
// s_l = 56;
// s_w = 85;
s_h = 20;

offset_top = 5;
// hive button
hb_d = 8;
hb_sep = 2;
// command button
cb_d = 6;
cb_h = 10;
cb_sep = 2;

// skrrrrrt
button_skirt = 1;

// completedDevice();
// boxHollow();
topBox();
bottomBox();

// Here there be modules

module completedDevice() {
    // The actual model
    boxWithScreen();

    color("red") {
        translate([20, 10, box_h - top_box_thick - 1]) {
            honeycomb(hb_d, hb_sep, button_skirt);
        }
    }

    color("purple") {
        translate([box_w - 25, 12, box_h - top_box_thick - 1])
        commandButtons(cb_d, cb_h, cb_sep, button_skirt);
    }

    color("pink") {
        translate([box_w - 6, box_l - 20, box_h - 5])
        rotate([0, 90, 0])
            commandButton(cb_d, cb_h + 5, cb_sep, button_skirt);
    }

}

module boxWithScreen() {
    difference() {
        translate([0, 0, box_h]) rotate([-90,0,0])
            roundedRect(box_w, box_h, box_l / 2, r = 4);
        translate([(box_w - s_w) / 2, box_l - s_l - offset_top, 5])
            cube([s_w, s_l ,box_h]);
        translate([box_thick, box_thick, box_thick])
        cube([box_w - box_thick * 2, box_l - box_thick * 2, box_h - box_thick - top_box_thick]);
    }
}

module boxHollow() {

    difference() {
        // The actual model
        boxWithScreen();

        translate([20, 10, box_h - top_box_thick - 1]) {
            honeycomb(hb_d, hb_sep, button_skirt);
        }

        translate([box_w - 25, 12, box_h - top_box_thick - 1])
        commandButtons(cb_d, cb_h, cb_sep, button_skirt);

        translate([box_w - 6, box_l - 20, box_h - 5])
        rotate([0, 90, 0])
            commandButton(cb_d, cb_h + 5, cb_sep, button_skirt);
    }
}

module topBox() {
    difference() {
        boxHollow();
        translate([-10, -10, 0])
        cube([200, 200, box_h / 2]);
    }
}

module bottomBox() {
    difference() {
        boxHollow();
        translate([-10, -10, box_h / 2])
        cube([200, 200, box_h]);
    }
}