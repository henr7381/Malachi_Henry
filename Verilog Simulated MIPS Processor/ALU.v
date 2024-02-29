module alu2b(a, b, sum, sel, g, p, Cin);
	input a, b, Cin;
	input [2:0] sel;
	output g, p;
	output reg sum;

	wire bint;

	assign bint = b ^ sel[0];
	assign g = a & bint; 
	assign p = a ^ bint; 

	always @ (*)
	begin
		case(sel)
			3'b000: sum = a ^ b;
			3'b001: sum = ~(a ^ b);
			3'b010: sum = a ^ bint ^ Cin;
			3'b011: sum = a ^ bint ^ Cin;
			3'b100: sum = a | b;
			3'b101: sum = ~(a | b);
			3'b110: sum = a & b;
			default: sum = 0;
		endcase
	end
endmodule

module lac2(g, p, c, gout, pout, cin);
	input [1:0] g, p;
	input cin;
	output [1:0] c;
	output gout, pout;

	assign c[1] = g[0] | (p[0] & cin);
	assign c[0] = cin;
	assign gout = g[1] | (g[0] & p[1]);
	assign pout = p[1] & p[0];
endmodule	

module lac4(g, p, c, gout, pout, cin);
	input[3:0] g, p;
	input cin;
	output [3:0] c;
	output gout, pout;
	
	wire [1:0] gint, pint, cint;

	// lac(g, p, c, gout, pout, cin)
	lac2 mod1 (g[1:0], p[1:0], c[1:0], gint[0], pint[0], cint[0]);
	lac2 mod2 (g[3:2], p[3:2], c[3:2], gint[1], pint[1], cint[1]);
	lac2 mod3 (gint, pint, cint, gout, pout, cin);
endmodule

module lac8(g, p, c, gout, pout, cin);
	input[7:0] g, p;
	input cin;
	output [7:0] c;
	output gout, pout;
	
	wire [1:0] gint, pint, cint;

	// lac(g, p, c, gout, pout, cin)
	lac4 mod1 (g[3:0], p[3:0], c[3:0], gint[0], pint[0], cint[0]);
	lac4 mod2 (g[7:4], p[7:4], c[7:4], gint[1], pint[1], cint[1]);
	lac2 mod3 (gint, pint, cint, gout, pout, cin);
endmodule

module lac16(g, p, c, gout, pout, cin);
	input[15:0] g, p;
	input cin;
	output [15:0] c;
	output gout, pout;
	
	wire [1:0] gint, pint, cint;

	// lac(g, p, c, gout, pout, cin)
	lac8 mod1 (g[7:0], p[7:0], c[7:0], gint[0], pint[0], cint[0]);
	lac8 mod2 (g[15:8], p[15:8], c[15:8], gint[1], pint[1], cint[1]);
	lac2 mod3 (gint, pint, cint, gout, pout, cin);
endmodule

module lac32(g, p, c, gout, pout, cin);
	input[31:0] g, p;
	input cin;
	output [31:0] c;
	output gout, pout;
	
	wire [1:0] gint, pint, cint;

	// lac(g, p, c, gout, pout, cin)
	lac16 mod1 (g[15:0], p[15:0], c[15:0], gint[0], pint[0], cint[0]);
	lac16 mod2 (g[31:16], p[31:16], c[31:16], gint[1], pint[1], cint[1]);
	lac2 mod3 (gint, pint, cint, gout, pout, cin);
endmodule

module project2b(a, b, d, Cin, Cout, V, S);
	input [31:0] a, b;
	input [2:0] S;
	input Cin;
	output [31:0] d;
	output V, Cout;

	wire [31:0] gout, pout, cout;
	wire g, p;

	// alu2b(a, b, sum, sel, g, p, Cin)
	alu2b mod1[31:0](a, b, d, S, gout, pout, cout);

	assign Cout = g | (p & Cin);
	assign V = Cout ^ cout[31];
	
	// lac32(g, p, c, gout, pout, cin)
	lac32 mod2(gout, pout, cout, g, p, Cin);	
endmodule
















