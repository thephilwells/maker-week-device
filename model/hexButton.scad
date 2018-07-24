module hexButton(b_d, button_skirt) {
    translate([button_skirt, button_skirt, 0])
    union() {
        linear_extrude(3) {
            translate([b_d / 2, b_d / 2, 0])
                circle(d = b_d, $fn=6);
        }
        
        linear_extrude(.5) {
            offset(r = button_skirt)
            translate([b_d / 2, b_d / 2, 0])
                circle(d = b_d, $fn=6);
        }
    }
}

module honeycomb(hb_d, hb_sep, button_skirt) {
    translate([0, 3, 0]) {
        hexButton(hb_d, button_skirt);
        translate([0, hb_d + hb_sep, 0])
            hexButton(hb_d, button_skirt);
        translate([hb_d + 1, 5, 0])
            hexButton(hb_d, button_skirt);
        translate([hb_d + 1, 15, 0])
            hexButton(hb_d, button_skirt);
        translate([hb_d + 1, -5, 0])
            hexButton(hb_d, button_skirt);
        translate([hb_d * 2 + hb_sep, 0, 0])
            hexButton(hb_d, button_skirt);
        translate([hb_d * 2 + hb_sep, hb_d + hb_sep , 0])
            hexButton(hb_d, button_skirt);
    }
}