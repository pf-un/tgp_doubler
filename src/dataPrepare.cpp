#include "host_graph_api.h"
#include "fpga_application.h"


unsigned int dataPrepareGetArg(graphInfo *info)
{
	return 0;
}

int dataPrepareProperty(graphInfo *info)
{
    auto *vertexPushinProp = (prop_t*)get_host_mem_pointer(MEM_ID_PUSHIN_PROP);
    int vertexNum = info->vertexNum;
    int alignedVertexNum = get_he_mem(MEM_ID_PUSHIN_PROP)->size / sizeof(prop_t);

    for (int i = 0; i < info->vertexNum; i++)			vertexPushinProp[i] = i+1;
    for (int i = vertexNum; i < alignedVertexNum; i++) 	vertexPushinProp[i] = 0;

    
    auto *edgeProp = (prop_t*)get_host_mem_pointer(MEM_ID_EDGE_PROP);
    int edgeNum = info->edgeNum;
    int alignedEdgeNum = get_he_mem(MEM_ID_EDGE_PROP)->size / sizeof(prop_t);

    for (int i = 0; i < edgeNum; i++) 				edgeProp[i] = 2;
    for (int i = edgeNum; i < alignedEdgeNum; i++)	edgeProp[i] = 0;
    
    
    return 0;
}
