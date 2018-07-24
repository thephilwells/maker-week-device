module commandButtons(cb_d, cb_h, cb_sep, button_skirt) {
    commandButton(cb_d, cb_h, cb_sep, button_skirt);
    translate([0, cb_d + cb_sep, 0])
        commandButton(cb_d, cb_h, cb_sep, button_skirt);
    translate([0, cb_d * 2 + cb_sep * 2, 0])
    commandButton(cb_d, cb_h, cb_sep, button_skirt);
}

module commandButton(cb_d, cb_h, cb_sep, button_skirt) {
    union() {
        linear_extrude(cb_h) {
            translate([cb_d / 2, cb_d / 2, 0])
                circle(d = cb_d, $fn=30);
        }

        linear_extrude(.5) {
            offset(r = button_skirt)
            translate([cb_d / 2, cb_d / 2, 0])
                circle(d = cb_d, $fn=30);
        }
    }
}
