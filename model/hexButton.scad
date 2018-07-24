module hexButton(b_d, button_skirt) {
    translate([button_skirt, button_skirt, 0])
    difference() {
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
        
        linear_extrude(2) {
            offset(r = -button_skirt)
            translate([b_d / 2, b_d / 2, 0])
                circle(d = b_d, $fn=6);
        }

    }
    translate([5, 5, 1])
        cylinder(r1 = 1, r2 = 1, h = 2, center = true, $fn = 20); 
}
