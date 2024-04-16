#include "LogisticHandler.h"
#include "ClusterGenerator.h"

void LogisticHandler::generateCluster(ClusterType clusterType, std::vector<POI> pointsOfInterests) {
	switch (clusterType)
	{
	case LogisticHandler::HIERARCHICAL:
		ClusterGenerator::getHierarchicalCluster(pointsOfInterests);
		break;
	case LogisticHandler::K_MEANS:
		ClusterGenerator::getK_MeansCluster(pointsOfInterests);
		break;
	default:
		break;
	}
}