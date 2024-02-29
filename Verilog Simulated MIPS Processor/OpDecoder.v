
module decode5to32(in, out);
	input [4:0] in;
	output reg [31:0] out;

	always @ (in)
	begin
		case(in)
			5'b00000: out <= 32'b0000_0000_0000_0000_0000_0000_0000_0001;
			5'b00001: out <= 32'b0000_0000_0000_0000_0000_0000_0000_0010;
			5'b00010: out <= 32'b0000_0000_0000_0000_0000_0000_0000_0100;
			5'b00011: out <= 32'b0000_0000_0000_0000_0000_0000_0000_1000;
			5'b00100: out <= 32'b0000_0000_0000_0000_0000_0000_0001_0000;
			5'b00101: out <= 32'b0000_0000_0000_0000_0000_0000_0010_0000;
			5'b00110: out <= 32'b0000_0000_0000_0000_0000_0000_0100_0000;
			5'b00111: out <= 32'b0000_0000_0000_0000_0000_0000_1000_0000;
			5'b01000: out <= 32'b0000_0000_0000_0000_0000_0001_0000_0000;
			5'b01001: out <= 32'b0000_0000_0000_0000_0000_0010_0000_0000;
			5'b01010: out <= 32'b0000_0000_0000_0000_0000_0100_0000_0000;
			5'b01011: out <= 32'b0000_0000_0000_0000_0000_1000_0000_0000;
			5'b01100: out <= 32'b0000_0000_0000_0000_0001_0000_0000_0000;
			5'b01101: out <= 32'b0000_0000_0000_0000_0010_0000_0000_0000;
			5'b01110: out <= 32'b0000_0000_0000_0000_0100_0000_0000_0000;
			5'b01111: out <= 32'b0000_0000_0000_0000_1000_0000_0000_0000;
			5'b10000: out <= 32'b0000_0000_0000_0001_0000_0000_0000_0000;
			5'b10001: out <= 32'b0000_0000_0000_0010_0000_0000_0000_0000;
			5'b10010: out <= 32'b0000_0000_0000_0100_0000_0000_0000_0000;
			5'b10011: out <= 32'b0000_0000_0000_1000_0000_0000_0000_0000;
			5'b10100: out <= 32'b0000_0000_0001_0000_0000_0000_0000_0000;
			5'b10101: out <= 32'b0000_0000_0010_0000_0000_0000_0000_0000;
			5'b10110: out <= 32'b0000_0000_0100_0000_0000_0000_0000_0000;
			5'b10111: out <= 32'b0000_0000_1000_0000_0000_0000_0000_0000;
			5'b11000: out <= 32'b0000_0001_0000_0000_0000_0000_0000_0000;
			5'b11001: out <= 32'b0000_0010_0000_0000_0000_0000_0000_0000;
			5'b11010: out <= 32'b0000_0100_0000_0000_0000_0000_0000_0000;
			5'b11011: out <= 32'b0000_1000_0000_0000_0000_0000_0000_0000;
			5'b11100: out <= 32'b0001_0000_0000_0000_0000_0000_0000_0000;
			5'b11101: out <= 32'b0010_0000_0000_0000_0000_0000_0000_0000;
			5'b11110: out <= 32'b0100_0000_0000_0000_0000_0000_0000_0000;
			5'b11111: out <= 32'b1000_0000_0000_0000_0000_0000_0000_0000;
		endcase
	end
endmodule


module mux (a, b, y, sel);
	input [31:0] a, b;
	output reg [31:0] y;
	input sel;
	
	always @ (*)
	begin
		case(sel)
			1'b1: y <= a;
			1'b0: y <= b;
		endcase
	end
endmodule


module DFF32(dbus, qbus, clk);
	input clk;
	input [31:0] dbus;
	output reg [31:0] qbus;

	always @ (posedge clk)
	begin
		qbus <= dbus;
	end
endmodule


module DFF3(dbus, qbus, clk);
	input clk;
	input [2:0] dbus;
	output reg [2:0] qbus;

	always @ (posedge clk)
	begin
		qbus <= dbus;
	end
endmodule


module DFF1(d, q, clk);
	input clk;
	input d;
	output reg q;

	always @ (posedge clk)
	begin
		q <= d;
	end
endmodule
	

module opdecoder(in, fin, immsel, S, cin);
	input [5:0] in;
	input [5:0] fin;
	output reg immsel, cin;
	output reg [2:0] S;
	
	always @ (*) 
	begin
		case(in)
			6'b000_001: 
				begin
					immsel <= 1'b1;
					cin <= 1'b0;
					S <= 3'b000;
				end
			6'b000_010: 
				begin
					immsel <= 1'b1;
					cin <= 1'b1;
					S <= 3'b011;
				end
			6'b000_011: 
				begin
					immsel <= 1'b1;
					cin <= 1'b0;
					S <= 3'b010;
				end
			6'b001_100: 
				begin
					immsel <= 1'b1;
					cin <= 1'b0;
					S <= 3'b100;
				end
			6'b001_111: 
				begin
					immsel <= 1'b1;
					cin <= 1'b0;
					S <= 3'b110;
				end
			6'b000_000: 
				begin
					case(fin)
						6'b000_001: 
							begin
								immsel <= 1'b0;
								cin <= 1'b0;
								S <= 3'b000;
							end
						6'b000_010: 
							begin
								immsel <= 1'b0;
								cin <= 1'b1;
								S <= 3'b011;
							end
						6'b000_011: 
							begin
								immsel <= 1'b0;
								cin <= 1'b0;
								S <= 3'b010;
							end
						6'b000_100: 
							begin
								immsel <= 1'b0;
								cin <= 1'b0;
								S <= 3'b100;
							end
						6'b000_111: 
							begin
								immsel <= 1'b0;
								cin <= 1'b0;
								S <= 3'b110;
							end
					endcase
				end
		endcase
	end
endmodule	


module Project5(ibus, clk, Aselect, Bselect, Dselect, Imm, S, Cin);
	input [31:0] ibus;
	input clk;
	output [31:0] Aselect, Dselect;
	output wire [31:0] Bselect;
	output [2:0] S;
	output Imm, Cin;
	
	wire [31:0] iclk, dwire, ddecoded;
	wire immsel, cindec;
	wire [2:0] seldec;
	
	DFF32 reg1 (ibus, iclk, clk);

	decode5to32 rs (iclk[25:21], Aselect);
	decode5to32 rt (iclk[20:16], Bselect);
	decode5to32 rd (iclk[15:11], dwire);
	opdecoder opdec (iclk[31:26], iclk[5:0], immsel, seldec, cindec); 
	
	mux Dsel (Bselect, dwire, ddecoded, immsel);
	
	DFF32 reg2a (ddecoded, Dselect, clk);
	DFF1 reg2b (immsel, Imm, clk);
	DFF3 reg2c(seldec, S, clk);
	DFF1 reg2d (cindec, Cin, clk);	
	
endmodule 