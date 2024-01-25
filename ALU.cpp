#include <ap_axi_sdata.h>
#include <cstdint>


typedef ap_axiu<32,1,1,1> AXI_DATA;





struct out{
	int32_t a;
	bool z,o,c;

};

out ALU(int32_t A, int32_t B, uint8_t CTRL){
#pragma HLS INTERFACE s_axilite port=return

#pragma HLS INTERFACE axis register port=A
#pragma HLS INTERFACE axis register port=B
	int32_t OUT;
#pragma HLS INTERFACE axis register port=OUT


	bool zero, overflow, carryout = 0;
	carryout = (static_cast<uint32_t>(A) + static_cast<uint32_t>(B)) > UINT32_MAX;
	overflow = (A > 0 && B > 0 && INT32_MAX - A < B) || (A < 0 && B < 0 && INT32_MIN - A > B);

	switch(CTRL){
	case 0b0000:
		OUT = A&B;
		break;
	case 0b0001:
		OUT = A|B;
		break;
	case 0b0010:
		OUT = A+B;
		break;
	case 0b0110:
		OUT = A-B;
		break;
	case 0b0111:
		if(A<B)
			OUT = 1;
		else
			OUT = 0;
        break;
	case 0b0100:
		OUT = !(A||B);
		break;
		}
	zero = (OUT == 0);
	return {OUT, zero, overflow,carryout};
}


