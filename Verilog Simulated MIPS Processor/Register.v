module negDFF32(dbus, qbus, clk);
	input clk;
	input [31:0] dbus;
	output reg [31:0] qbus;

	always @ (negedge clk)
	begin
		qbus <= dbus;
	end
endmodule


module tribuf32(dbus, qbus, EN);
	input EN;
	input [31:0] dbus;
	output reg [31:0] qbus;

	always @ (*)
	begin
		if(EN == 1)
			qbus <= dbus;
		else
			qbus <= 32'bZZZZ_ZZZZ_ZZZZ_ZZZZ_ZZZZ_ZZZZ_ZZZZ_ZZZZ;
	end
endmodule


module addreg32(abus, bbus, dbus, clk, bsel, asel, dsel);
	input clk, bsel, asel, dsel;
	output [31:0] abus, bbus;
	input [31:0] dbus;

	wire [31:0] unsplit;
	wire cleanclk;

	assign cleanclk = clk & dsel;
	
	negDFF32 mod1 (dbus, unsplit, cleanclk);
	tribuf32 mod2 (unsplit, abus, asel);
	tribuf32 mod3 (unsplit, bbus, bsel);

endmodule


module addreg0(abus, bbus, dbus, bsel, asel, dsel);
	input bsel, asel, dsel;
	input [31:0] abus, bbus, dbus;

	tribuf32 mod2 (32'b0, abus, asel);
	tribuf32 mod3 (32'b0, bbus, bsel);

endmodule


module Project4(abus, bbus, dbus, clk, Bselect, Aselect, Dselect);
	input clk;
	input [31:0]dbus, Bselect, Aselect, Dselect;
	output [31:0] abus, bbus;

	addreg0 mod1 (abus, bbus, dbus, Bselect[0], Aselect[0], Dselect[0]);
	addreg32 mod2[30:0] (abus, bbus, dbus, clk, Bselect[31:1], Aselect[31:1], Dselect[31:1]);

endmodule