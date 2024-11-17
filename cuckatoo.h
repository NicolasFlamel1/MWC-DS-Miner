// Header guard
#ifndef CUCKATOO_H
#define CUCKATOO_H


// Header files
using namespace std;


// Structures

// Cuckatoo node connection structure
struct CuckatooNodeConnection {

	// Previous node connection link
	const CuckatooNodeConnection *previousNodeConnection;
	
	// Node
	uint32_t node;
	
	// Edge index
	uint32_t edgeIndex;
};


// Function prototypes

// Get cuckatoo solution
ITCM_CODE static inline bool getCuckatooSolution(const uint32_t edgeIndex, const uint32_t uNode, const uint32_t vNode, CuckatooNodeConnection *nodeConnections, HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestUNodesConnection, HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestVNodesConnection, uint32_t solution[SOLUTION_SIZE]);

// Search u node connections for cuckatoo solution
ITCM_CODE static inline bool searchUNodeConnectionsForCuckatooSolution(const int cycleSize, const uint32_t node, const uint32_t *edgeIndex, const uint32_t rootNode, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestUNodesConnection, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestVNodesConnection, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedUNodePairs, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedVNodePairs);

// Search v node connections for cuckatoo solution
ITCM_CODE static inline bool searchVNodeConnectionsForCuckatooSolution(const int cycleSize, const uint32_t node, const uint32_t *edgeIndex, const uint32_t rootNode, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestUNodesConnection, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestVNodesConnection, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedUNodePairs, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedVNodePairs);


// Supporting function implementation

// Get cuckatoo solution
bool getCuckatooSolution(const uint32_t edgeIndex, const uint32_t uNode, const uint32_t vNode, CuckatooNodeConnection *nodeConnections, HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestUNodesConnection, HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestVNodesConnection, uint32_t solution[SOLUTION_SIZE]) {

	// Replace newest node connections for the nodes on both partitions and add node connections to list
	nodeConnections[0] = {newestUNodesConnection.replace(uNode, &nodeConnections[0]), uNode, edgeIndex};
	nodeConnections[1] = {newestVNodesConnection.replace(vNode, &nodeConnections[1]), vNode, edgeIndex};
	
	// Check if both nodes have a pair
	if(newestUNodesConnection.contains(uNode ^ 1) && newestVNodesConnection.contains(vNode ^ 1)) {
	
		// Create visited node pairs
		HashTable<uint32_t, SOLUTION_SIZE / 2> visitedUNodePairs;
		HashTable<uint32_t, SOLUTION_SIZE / 2> visitedVNodePairs;
		
		// Go through all nodes in the cycle
		const uint32_t *index = &edgeIndex;
		uint32_t node = uNode;
		for(int cycleSize = 1;; cycleSize += 2) {
		
			// Set that node pair has been visited
			visitedUNodePairs.setUnique(node >> 1, index);
			
			// Check if node's pair has more than one connection
			const CuckatooNodeConnection *nodeConnection = newestUNodesConnection.get(node ^ 1);
			if(nodeConnection->previousNodeConnection) {
			
				// Go through all of the node's pair's connections
				for(; nodeConnection; nodeConnection = nodeConnection->previousNodeConnection) {
				
					// Check if the connected node's pair wasn't already visited
					if(!visitedVNodePairs.contains((nodeConnection + 1)->node >> 1)) {
					
						// Check if cycle is complete
						if(((nodeConnection + 1)->node ^ 1) == vNode) {
						
							// Check if cycle is a solution
							if(cycleSize == SOLUTION_SIZE - 1) {
							
								// Get solution from visited nodes
								visitedUNodePairs.getValues(solution);
								visitedVNodePairs.getValues(&solution[SOLUTION_SIZE / 2]);
								solution[SOLUTION_SIZE - 1] = (nodeConnection + 1)->edgeIndex;
								
								// Sort solution in ascending order
								sort(solution, solution + SOLUTION_SIZE);
								
								// Return true
								return true;
							}
						}
						
						// Otherwise check if cycle could be as solution
						else if(cycleSize != SOLUTION_SIZE - 1) {
						
							// Check if the connected node has a pair
							if(newestVNodesConnection.contains((nodeConnection + 1)->node ^ 1)) {
							
								// Check if solution was found at the connected node's pair
								if(searchVNodeConnectionsForCuckatooSolution(cycleSize + 1, (nodeConnection + 1)->node ^ 1, &(nodeConnection + 1)->edgeIndex, vNode, newestUNodesConnection, newestVNodesConnection, visitedUNodePairs, visitedVNodePairs)) {
								
									// Get solution from visited nodes
									visitedUNodePairs.getValues(solution);
									visitedVNodePairs.getValues(&solution[SOLUTION_SIZE / 2]);
									
									// Sort solution in ascending order
									sort(solution, solution + SOLUTION_SIZE);
									
									// Return true
									return true;
								}
							}
						}
					}
				}
				
				// Break
				break;
			}
			
			// Go to node's pair opposite end and get its edge index
			index = &(nodeConnection + 1)->edgeIndex;
			node = (nodeConnection + 1)->node;
			
			// Check if node pair was already visited
			if(visitedVNodePairs.contains(node >> 1)) {
			
				// Break
				break;
			}
			
			// Check if cycle is complete
			if((node ^ 1) == vNode) {
			
				// Check if cycle is a solution
				if(cycleSize == SOLUTION_SIZE - 1) {
				
					// Get solution from visited nodes
					visitedUNodePairs.getValues(solution);
					visitedVNodePairs.getValues(&solution[SOLUTION_SIZE / 2]);
					solution[SOLUTION_SIZE - 1] = *index;
					
					// Sort solution in ascending order
					sort(solution, solution + SOLUTION_SIZE);
					
					// Return true
					return true;
				}
				
				// Break
				break;
			}
			
			// Check if cycle isn't a solution
			if(cycleSize == SOLUTION_SIZE - 1) {
			
				// Break
				break;
			}
			
			// Check if node doesn't have a pair
			if(!newestVNodesConnection.contains(node ^ 1)) {
			
				// break
				break;
			}
			
			// Set that node pair has been visited
			visitedVNodePairs.setUnique(node >> 1, index);
			
			// Check if node's pair has more than one connection
			nodeConnection = newestVNodesConnection.get(node ^ 1);
			if(nodeConnection->previousNodeConnection) {
			
				// Go through all of the node's pair's connections
				for(; nodeConnection; nodeConnection = nodeConnection->previousNodeConnection) {
				
					// Check if the connected node has a pair
					if(newestUNodesConnection.contains((nodeConnection - 1)->node ^ 1)) {
					
						// Check if the connected node's pair wasn't already visited
						if(!visitedUNodePairs.contains((nodeConnection - 1)->node >> 1)) {
						
							// Check if solution was found at the connected node's pair
							if(searchUNodeConnectionsForCuckatooSolution(cycleSize + 2, (nodeConnection - 1)->node ^ 1, &(nodeConnection - 1)->edgeIndex, vNode, newestUNodesConnection, newestVNodesConnection, visitedUNodePairs, visitedVNodePairs)) {
							
								// Get solution from visited nodes
								visitedUNodePairs.getValues(solution);
								visitedVNodePairs.getValues(&solution[SOLUTION_SIZE / 2]);
								
								// Sort solution in ascending order
								sort(solution, solution + SOLUTION_SIZE);
								
								// Return true
								return true;
							}
						}
					}
				}
				
				// Break
				break;
			}
			
			// Go to node's pair opposite end and get its edge index
			index = &(nodeConnection - 1)->edgeIndex;
			node = (nodeConnection - 1)->node;
			
			// Check if node pair was already visited
			if(visitedUNodePairs.contains(node >> 1)) {
			
				// Break
				break;
			}
			
			// Check if node doesn't have a pair
			if(!newestUNodesConnection.contains(node ^ 1)) {
			
				// break
				break;
			}
		}
	}
	
	// Return false
	return false;
}

// Search u node connections for cuckatoo solution
bool searchUNodeConnectionsForCuckatooSolution(const int cycleSize, const uint32_t node, const uint32_t *edgeIndex, const uint32_t rootNode, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestUNodesConnection, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestVNodesConnection, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedUNodePairs, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedVNodePairs) {

	// Set that node pair has been visited
	const uint32_t visitedNodePairIndex = visitedUNodePairs.setUniqueAndGetIndex(node >> 1, edgeIndex);
	
	// Go through all of the node's connections
	for(const CuckatooNodeConnection *nodeConnection = newestUNodesConnection.get(node); nodeConnection; nodeConnection = nodeConnection->previousNodeConnection) {
	
		// Check if the connected node's pair wasn't already visited
		if(!visitedVNodePairs.contains((nodeConnection + 1)->node >> 1)) {
		
			// Check if cycle is complete
			if(((nodeConnection + 1)->node ^ 1) == rootNode) {
			
				// Check if cycle is a solution
				if(cycleSize == SOLUTION_SIZE - 1) {
				
					// Set that the connected node's pair has been visited
					visitedVNodePairs.setUnique((nodeConnection + 1)->node >> 1, &(nodeConnection + 1)->edgeIndex);
					
					// Return true
					return true;
				}
			}
			
			// Otherwise check if cycle could be as solution
			else if(cycleSize != SOLUTION_SIZE - 1) {
			
				// Check if the connected node has a pair
				if(newestVNodesConnection.contains((nodeConnection + 1)->node ^ 1)) {
				
					// Check if solution was found at the connected node's pair
					if(searchVNodeConnectionsForCuckatooSolution(cycleSize + 1, (nodeConnection + 1)->node ^ 1, &(nodeConnection + 1)->edgeIndex, rootNode, newestUNodesConnection, newestVNodesConnection, visitedUNodePairs, visitedVNodePairs)) {
					
						// Return true
						return true;
					}
				}
			}
		}
	}
	
	// Set that node pair hasn't been visited
	visitedUNodePairs.removeMostRecentSetUique(visitedNodePairIndex);
	
	// Return false
	return false;
}

// Search v node connections for cuckatoo solution
bool searchVNodeConnectionsForCuckatooSolution(const int cycleSize, const uint32_t node, const uint32_t *edgeIndex, const uint32_t rootNode, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestUNodesConnection, const HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> &newestVNodesConnection, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedUNodePairs, HashTable<uint32_t, SOLUTION_SIZE / 2> &visitedVNodePairs) {

	// Set that node pair has been visited
	const uint32_t visitedNodePairIndex = visitedVNodePairs.setUniqueAndGetIndex(node >> 1, edgeIndex);
	
	// Go through all of the node's connections
	for(const CuckatooNodeConnection *nodeConnection = newestVNodesConnection.get(node); nodeConnection; nodeConnection = nodeConnection->previousNodeConnection) {
	
		// Check if the connected node has a pair
		if(newestUNodesConnection.contains((nodeConnection - 1)->node ^ 1)) {
		
			// Check if the connected node's pair wasn't already visited
			if(!visitedUNodePairs.contains((nodeConnection - 1)->node >> 1)) {
			
				// Check if solution was found at the connected node's pair
				if(searchUNodeConnectionsForCuckatooSolution(cycleSize + 1, (nodeConnection - 1)->node ^ 1, &(nodeConnection - 1)->edgeIndex, rootNode, newestUNodesConnection, newestVNodesConnection, visitedUNodePairs, visitedVNodePairs)) {
				
					// Return true
					return true;
				}
			}
		}
	}
	
	// Set that node pair hasn't been visited
	visitedVNodePairs.removeMostRecentSetUique(visitedNodePairIndex);
	
	// Return false
	return false;
}


#endif
