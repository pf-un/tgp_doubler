#include <iostream>

#include "host_graph_api.h"
#include "host_graph_verification.h"

graphInfo graphDataInfo;

void print_props(prop_t *props) {
    int acc = 0;
    
    std::cout << "Property for \"first 10\" vertices:" << "\n";
    for (int i = 0; i < graphDataInfo.vertexNum; ++i) {
		if (props[i] != 0 ) acc += 1;
		
		if (i < 10 ) std::cout << props[i] << "\n";

    }
    std::cout << "Number of vertices with non-null property:" << acc << "\n\n";
	
}

int main(int argc, char **argv) {

    char * xcl_file = NULL;
    if (argc > 1) xcl_file = argv[1];

    std::string gName;
    if (argc > 2) gName = argv[2];


    acceleratorInit("graph_fpga", xcl_file);
    acceleratorDataLoad(gName, "normal", &graphDataInfo);
    
    acceleratorDataPreprocess(&graphDataInfo);
    acceleratorCModelDataPreprocess(&graphDataInfo);



    acceleratorSuperStep(0, &graphDataInfo);
    acceleratorCModelSuperStep(0, &graphDataInfo);


	prop_t *props = (prop_t*) get_host_mem_pointer(MEM_ID_PUSHIN_PROP);
    prop_t *props_mapped = (prop_t*) get_host_mem_pointer(MEM_ID_PUSHIN_PROP_MAPPED);
    
    print_props(props);
    print_props(props_mapped);


    acceleratorDeinit();
    return 0;
}
