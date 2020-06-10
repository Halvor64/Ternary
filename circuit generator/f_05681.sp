.subckt f_05681 a b out vdd


xp0 up out out ptype 1.018nm
xn0 out out down ntype 1.018nm
******** UpVddGnd ********


xp2 vdd b p0 ptype 0.783nm

xp3 p0 a out ptype 0.783nm

xn4 vdd a p1 ntype 0.783nm

xn5 p1 b p2 ntype 1.487nm

xp6 p2 b out ptype 1.487nm

xn7 vdd b p3 ntype 0.783nm

xn8 p3 a p4 ntype 1.487nm

xp9 p4 a out ptype 1.487nm

******** DownVddGnd ********
xp10 gnd b p5 ptype 0.783nm

xn11 p5 a p6 ntype 1.487nm

xp12 p6 a out ptype 1.487nm

xp13 gnd a p7 ptype 0.783nm

xn14 p7 b p8 ntype 1.487nm

xp15 p8 b out ptype 1.487nm

xn16 gnd b p9 ntype 0.783nm

xn17 p9 a out ntype 0.783nm

******** UpHalfVdd ********
xn18 vdd b p10 ntype 0.783nm

xp19 p10 a up ptype 1.487nm

xn20 vdd a p10 ntype 0.783nm

xp21 p10 b up ptype 1.487nm

xn22 vdd b p11 ntype 1.487nm

xp23 p11 b p12 ptype 1.487nm

xn24 p12 a up ntype 1.487nm

******** DownHalfVdd ********
xn25 gnd a p13 ntype 1.487nm

xp26 p13 a p14 ptype 1.487nm

xp27 p14 b out ptype 1.487nm

xn28 gnd a p15 ntype 1.487nm

xp29 p15 b down ptype 0.783nm

xp30 gnd a p15 ptype 0.783nm

xn31 gnd b down ntype 1.487nm


.end

