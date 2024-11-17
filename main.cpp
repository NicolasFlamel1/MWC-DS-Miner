// Constants

// Bits in a byte
#define BITS_IN_A_BYTE 8

// Bytes in a kilobyte
#define BYTES_IN_A_KILOBYTE 1024

// Kilobytes in a megabyte
#define KILOBYTES_IN_A_MEGABYTE 1024

// Milliseconds in a second
#define MILLISECONDS_IN_A_SECOND 1000

// Check if using cuckatoo18
#ifdef CUCKATOO18

	// Edge bits
	#define EDGE_BITS 18
	
	// Trimming rounds
	#define TRIMMING_ROUNDS 4
	
	// Local RAM size
	#define LOCAL_RAM_SIZE ((1 << EDGE_BITS) / BITS_IN_A_BYTE)
	
	// Secondary local RAM size
	#define SECONDARY_LOCAL_RAM_SIZE LOCAL_RAM_SIZE
	
// Otherwise
#else

	// Edge bits
	#define EDGE_BITS 31
	
	// Trimming rounds
	#define TRIMMING_ROUNDS 380
	
	// Local RAM size
	#define LOCAL_RAM_SIZE (2 * KILOBYTES_IN_A_MEGABYTE * BYTES_IN_A_KILOBYTE)
	
	// Secondary local RAM size
	#define SECONDARY_LOCAL_RAM_SIZE (1 * KILOBYTES_IN_A_MEGABYTE * BYTES_IN_A_KILOBYTE)
#endif

// Number of edges
#define NUMBER_OF_EDGES (static_cast<uint32_t>(1) << EDGE_BITS)

// Bytes per bitmap
#define BYTES_PER_BITMAP (NUMBER_OF_EDGES / BITS_IN_A_BYTE)

// Node mask
#define NODE_MASK (NUMBER_OF_EDGES - 1)

// BLAKE2b hash size
#define BLAKE2B_HASH_SIZE 32

// Secp256k1 private key size
#define SECP256K1_PRIVATE_KEY_SIZE 32

// Header size
#define HEADER_SIZE (sizeof(uint16_t) + sizeof(uint64_t) + sizeof(int64_t) + BLAKE2B_HASH_SIZE + BLAKE2B_HASH_SIZE + BLAKE2B_HASH_SIZE + BLAKE2B_HASH_SIZE + BLAKE2B_HASH_SIZE + SECP256K1_PRIVATE_KEY_SIZE + sizeof(uint64_t) + sizeof(uint64_t) + sizeof(uint64_t) + sizeof(uint32_t))

// Solution size
#define SOLUTION_SIZE 42

// Stratum settings file
#define STRATUM_SETTINGS_FILE "stratum_server_settings.txt"

// Stratum settings file max line size
#define STRATUM_SETTINGS_FILE_MAX_LINE_SIZE BYTES_IN_A_KILOBYTE

// Process stratum server response interval seconds
#define PROCESS_STRATUM_SERVER_RESPONSE_INTERVAL_SECONDS 10

// Process stratum server response timer
#define PROCESS_STRATUM_SERVER_RESPONSE_TIMER 0

// Socket timeout timer
#define SOCKET_TIMEOUT_TIMER 1

// No stratum server response disconnect seconds
#define NO_STRATUM_SERVER_RESPONSE_DISCONNECT_SECONDS 30

// Stratum server response buffer size
#define STRATUM_SERVER_RESPONSE_BUFFER_SIZE (10 * BYTES_IN_A_KILOBYTE)

// Frames per second
#define FRAMES_PER_SECOND 60

// Reconnect delay seconds
#define RECONNECT_DELAY_SECONDS 5

// Send timeout milliseconds
#define SEND_TIMEOUT_MILLISECONDS (30 * MILLISECONDS_IN_A_SECOND)

// Receive timeout milliseconds
#define RECEIVE_TIMEOUT_MILLISECONDS (30 * MILLISECONDS_IN_A_SECOND)

// Edges bitmap file
#define EDGES_BITMAP_FILE "edges_bitmap.bin"

// Max number of edges after trimming
#define MAX_NUMBER_OF_EDGES_AFTER_TRIMMING 65535

// To string
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

// Check if using Linux
#ifdef __linux__

	// Replacement functions
	
	// Print console
	struct PrintConsole {
	
		// Cursor y
		const int cursorY = 24;
	};
	
	// Console demo init
	#define consoleDemoInit() (new PrintConsole)
	
	// Close socket
	#define closesocket close
	
	// FAT init default
	#define fatInitDefault() !chdir("SD")
	
	// SWI wait for vblank
	#define swiWaitForVBlank() this_thread::sleep_for(static_cast<chrono::milliseconds>(MILLISECONDS_IN_A_SECOND / FRAMES_PER_SECOND))
	
	// Has RAM expansion pak
	#define HAS_RAM_EXPANSION_PAK false
	
	// Check if has RAM expansion pak
	#if HAS_RAM_EXPANSION_PAK
	
		// RAM init
		#define ram_init(x) true
		
		// RAM size
		#define ram_size() static_cast<uint32_t>(256 * KILOBYTES_IN_A_MEGABYTE * BYTES_IN_A_KILOBYTE)
		
		// RAM unlock
		#define ram_unlock() (new volatile uint16_t[ram_size() / sizeof(volatile uint16_t)])
		
	// Otherwise
	#else
	
		// RAM init
		#define ram_init(x) false
		
		// RAM size
		#define ram_size() static_cast<uint32_t>(0)
		
		// RAM unlock
		#define ram_unlock() static_cast<volatile uint16_t *>(nullptr)
	#endif
	
	// RAM lock
	#define ram_lock void
	
	// IRQ disable
	#define irqDisable(x) void()
	
	// IRQ enable
	#define irqEnable(x) void()
	
	// Wi-Fi init default
	#define Wifi_InitDefault(x) true
	
	// Wi-Fi timer
	#define Wifi_Timer void
	
	// CPU start timing
	#define cpuStartTiming void
	
	// CPU end timing
	#define cpuEndTiming void
	
	// Timer ticks to milliseconds
	#define timerTicks2msec(x) 0
	
	// Scan keys
	#define scanKeys void
	
	// Keys Down
	#define keysDown() true
	
	// Key A
	#define KEY_A true
	
	// Instruction tightly coupled memory
	#define ITCM_CODE
	
	// Main RAM 16
	#define MAINRAM16 static_cast<uint16_t *>(nullptr)
	
	// Main RAM 32
	#define MAINRAM32 static_cast<uint32_t *>(nullptr)
	
	// Is DSi mode
	#define isDSiMode() false
	
	// iprintf
	#define iprintf printf
	
	// siprintf
	#define siprintf sprintf
#endif


// Check if using Linux
#ifdef __linux__

	// Header files
	#include <sys/ioctl.h>
	#include <thread>
	
// Otherwise
#else

	// Header files
	#define _GNU_SOURCE
	#include <sys/types.h>
	#include <nds.h>
	#include <dswifi9.h>
	#include <fat.h>
	#include <filesystem.h>
	#include <sys/select.h>
	#include <netinet/in.h>
	#include "./model.h"
	#include "./ram.h"
#endif

// Header files
#include <algorithm>
#include <alloca.h>
#include <cinttypes>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <random>
#include "./blake2b.h"
#include "./hash_table.h"
#include "./cuckatoo.h"
#include "./siphash.h"

using namespace std;


// Global variables

// Console
static PrintConsole *console;

// Next job height
static uint64_t nextJobHeight;

// Next job ID
static uint64_t nextJobId;

// Next job header
static uint8_t nextJobHeader[HEADER_SIZE];

// New next job
static bool newNextJob;


// Function prototypes

// Wait for input to exit
ITCM_CODE [[noreturn]] static inline void waitForInputToExit();

// Display model
ITCM_CODE static inline void displayModel();

// Connect to stratum server
static inline unique_ptr<int, void(*)(int *)> connectToStratumServer();

// Process stratum server response
ITCM_CODE static inline bool processStratumServerResponse(char response[STRATUM_SERVER_RESPONSE_BUFFER_SIZE]);

// Send full
ITCM_CODE static inline bool sendFull(const int socketDescriptor, const char *data, size_t size);

// Receive full
ITCM_CODE static inline bool receiveFull(const int socketDescriptor, char *data, const size_t size);

// Mine job
ITCM_CODE static inline bool mineJob(const uint8_t jobHeader[HEADER_SIZE], const uint64_t jobNonce, volatile uint16_t *expansionRam, uint32_t solution[SOLUTION_SIZE]);

// Trim edges
ITCM_CODE static inline bool trimEdges(const uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &sipHashKeys, fstream &edgesBitmapFile, volatile uint16_t *expansionRam);

// Search remaining edges
ITCM_CODE static inline bool searchRemainingEdges(const uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &sipHashKeys, fstream &edgesBitmapFile, uint32_t solution[SOLUTION_SIZE]);


// Main function
ITCM_CODE int main() {

	// Check if configuring bottom screen for console failed
	console = consoleDemoInit();
	if(!console) {
	
		// Return failure
		return EXIT_FAILURE;
	}
	
	// Display message
	cout << "MWC DS Miner" << flush;
	
	// Check if today is MimbleWimble Coin's birthday
	const time_t timestamp = time(nullptr);
	const tm *localTime = localtime(&timestamp);
	if(localTime->tm_mon == 11 - 1 && localTime->tm_mday == 11) {
	
		// Display message
		cout << endl << "Happy birthday MimbleWimble Coin" << flush;
	}
	
	// Display model
	displayModel();
	
	// Check if initializing file system failed
	if(!fatInitDefault()) {
	
		// Display message
		cout << endl << "Initializing file system failed" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Check if not using a DSi and a RAM expansion pak exists
	volatile uint16_t *expansionRam = nullptr;
	if(!isDSiMode() && ram_init(DETECT_RAM)) {
	
		// Check if RAM expansion pak's RAM is smaller than local RAM or isn't a power of two
		if(ram_size() <= LOCAL_RAM_SIZE || !has_single_bit(ram_size())) {
		
			// Display message
			cout << endl << "Not using RAM expansion pak" << flush;
		}
		
		// Otherwise
		else {
		
			// Set expansion RAM to RAM expansion pak's RAM
			expansionRam = ram_unlock();
			
			// Automatically free RAM expansion pak's RAM when done
			static const unique_ptr<int, void(*)(void *)> expansionRamUniquePointer(reinterpret_cast<int *>(const_cast<uint16_t *>(expansionRam)), [] ITCM_CODE (void *) {
			
				// Lock RAM expansion pak's RAM
				ram_lock();
			});
			
			// Display message
			cout << endl << "Using RAM expansion pak" << flush;
		}
	}
	
	// Otherwise
	else {
	
		// Display message
		cout << endl << "No RAM expansion pak detected" << flush;
	}
	
	// Create random number generator
	mt19937_64 randomNumberGenerator(timestamp);
	
	// Initialize socket
	static unique_ptr<int, void(*)(int *)> socketDescriptorUniquePointer(nullptr, [] ITCM_CODE (int *) {});
	
	// Initialize seconds since no response
	static int secondsSinceNoResponse = 0;
	
	// Check if not using Linux
	#ifndef __linux__
	
		// Start process response from stratum server timer
		static int secondsSinceLastProcess = 0;
		timerStart(PROCESS_STRATUM_SERVER_RESPONSE_TIMER, ClockDivider_1024, TIMER_FREQ_1024(1), [] ITCM_CODE () {
		
			// Update seconds since no response
			++secondsSinceNoResponse;
			
			// Check if time to process response from stratum server
			if(++secondsSinceLastProcess == PROCESS_STRATUM_SERVER_RESPONSE_INTERVAL_SECONDS) {
			
				// Reset seconds since last process
				secondsSinceLastProcess = 0;
				
				// Check if connected to stratum server
				if(socketDescriptorUniquePointer) {
				
					// Check if getting if a request can be sent to stratum server failed
					fd_set writeSocketDescriptorsSet;
					FD_ZERO(&writeSocketDescriptorsSet);
					FD_SET(*socketDescriptorUniquePointer, &writeSocketDescriptorsSet);
					timeval timeout = {};
					const int requestAvailable = select(1, nullptr, &writeSocketDescriptorsSet, nullptr, &timeout);
					if(requestAvailable == -1) {
					
						// Disconnect from stratum server
						socketDescriptorUniquePointer.reset();
						
						// Return
						return;
					}
					
					// Otherwise check if a request can be sent to stratum server
					else if(requestAvailable) {
					
						// Check if sending keepalive request to stratum server failed
						if(send(*socketDescriptorUniquePointer, "{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"keepalive\",\"params\":null}\n", sizeof("{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"keepalive\",\"params\":null}\n") - sizeof('\0'), 0) != sizeof("{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"keepalive\",\"params\":null}\n") - sizeof('\0')) {
						
							// Disconnect from stratum server
							socketDescriptorUniquePointer.reset();
							
							// Return
							return;
						}
					}
					
					// Go through all responses from stratum server
					fd_set readSocketDescriptorsSet;
					FD_ZERO(&readSocketDescriptorsSet);
					FD_SET(*socketDescriptorUniquePointer, &readSocketDescriptorsSet);
					int responseAvailable;
					char response[STRATUM_SERVER_RESPONSE_BUFFER_SIZE];
					do {
					
						// Check if getting if a response from stratum server is available failed
						timeout = {};
						responseAvailable = select(1, &readSocketDescriptorsSet, nullptr, nullptr, &timeout);
						if(responseAvailable == -1) {
						
							// Disconnect from stratum server
							socketDescriptorUniquePointer.reset();
							
							// Break
							break;
						}
						
						// Otherwise check if a response is available from stratum server
						else if(responseAvailable) {
						
							// Check if receiving response from stratum server failed
							int responseSize = recv(*socketDescriptorUniquePointer, response, sizeof(response) - sizeof('\0'), MSG_PEEK);
							if(responseSize <= 0) {
							
								// Disconnect from stratum server
								socketDescriptorUniquePointer.reset();
								
								// Break
								break;
							}
							
							// Check if full response wasn't received
							if(!memchr(response, '\n', responseSize)) {
							
								// Check if response buffer is full
								if(responseSize == sizeof(response) - sizeof('\0')) {
								
									// Disconnect from stratum server
									socketDescriptorUniquePointer.reset();
								}
								
								// Break
								break;
							}
							
							// Check if receiving response from stratum server failed
							responseSize = recv(*socketDescriptorUniquePointer, response, sizeof(response) - sizeof('\0'), 0);
							if(responseSize <= 0) {
							
								// Disconnect from stratum server
								socketDescriptorUniquePointer.reset();
								
								// Break
								break;
							}
							
							// Null terminate response
							response[responseSize] = '\0';
							
							// Process response
							processStratumServerResponse(response);
							
							// Reset seconds since no response
							secondsSinceNoResponse = 0;
						}
						
						// Otherwise check if no response has been received from stratum server for awhile
						else if(secondsSinceNoResponse >= NO_STRATUM_SERVER_RESPONSE_DISCONNECT_SECONDS) {
						
							// Disconnect from stratum server
							socketDescriptorUniquePointer.reset();
						}
						
					} while(responseAvailable);
				}
			}
		});
	#endif
	
	// Loop forever
	while(true) {
	
		// Disable process response from stratum server timer interrupt
		irqDisable(IRQ_TIMER(PROCESS_STRATUM_SERVER_RESPONSE_TIMER));
		
		// Check if connecting to stratum server failed
		socketDescriptorUniquePointer = connectToStratumServer();
		if(!socketDescriptorUniquePointer) {
		
			// Display message
			cout << endl << "Retrying in " TO_STRING(RECONNECT_DELAY_SECONDS) " seconds" << flush;
			
			// Go through all frames to wait before reconnecting
			for(int i = 0; i < RECONNECT_DELAY_SECONDS * FRAMES_PER_SECOND; ++i) {
			
				// Wait for vertical blank
				swiWaitForVBlank();
			}
		}
		
		// Otherwise
		else {
		
			// Reset seconds since no response
			secondsSinceNoResponse = 0;
			
			// Loop forever
			uint64_t jobHeight = 0;
			uint64_t jobId = 0;
			uint8_t jobHeader[HEADER_SIZE];
			uint64_t jobNonce = 0;
			while(true) {
			
				// Disable process response from stratum server timer interrupt
				irqDisable(IRQ_TIMER(PROCESS_STRATUM_SERVER_RESPONSE_TIMER));
				
				// Check if not connected to stratum server
				if(!socketDescriptorUniquePointer) {
				
					// Display message
					cout << endl << "Disconnected from stratum server" << flush;
					
					// Break
					break;
				}
				
				// Check if new next job exists
				if(newNextJob) {
				
					// Set new next job to false
					newNextJob = false;
					
					// Set job height to next job height
					jobHeight = nextJobHeight;
					
					// Set job ID to next job ID
					jobId = nextJobId;
					
					// Set job header to next job header
					memcpy(jobHeader, nextJobHeader, sizeof(nextJobHeader));
					
					// Create random job nonce
					jobNonce = randomNumberGenerator();
					
					// Display message
					cout << endl << "Got new job from stratum server" << flush;
					
					// Display message
					cout << endl << "Mining job" << flush;
				}
				
				// Otherwise
				else {
				
					// Increment job nonce
					++jobNonce;
					
					// Display message
					cout << endl << "Mining job with different nonce" << flush;
				}
				
				// Enable process response from stratum server timer interrupt
				irqEnable(IRQ_TIMER(PROCESS_STRATUM_SERVER_RESPONSE_TIMER));
				
				// Check if mining job found a solution
				uint32_t solution[SOLUTION_SIZE];
				if(mineJob(jobHeader, jobNonce, expansionRam, solution)) {
				
					// Check if creating submit request failed
					char submitRequest[sizeof("{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"submit\",\"params\":{\"edge_bits\":" TO_STRING(EDGE_BITS) ",\"height\":") - sizeof('\0') + sizeof("18446744073709551615") - sizeof('\0') + sizeof(",\"job_id\":") - sizeof('\0') + sizeof("18446744073709551615") - sizeof('\0') + sizeof(",\"nonce\":") - sizeof('\0') + sizeof("18446744073709551615") - sizeof('\0') + sizeof(",\"pow\":[") - sizeof('\0') + (sizeof("4294967295,") - sizeof('\0')) * SOLUTION_SIZE - sizeof(',') + sizeof("]}}\n")];
					const int requestSize = siprintf(submitRequest, "{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"submit\",\"params\":{\"edge_bits\":" TO_STRING(EDGE_BITS) ",\"height\":%" PRIu64 ",\"job_id\":%" PRIu64 ",\"nonce\":%" PRIu64 ",\"pow\":[%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 ",%" PRIu32 "]}}\n", jobHeight, jobId, jobNonce, solution[0], solution[1], solution[2], solution[3], solution[4], solution[5], solution[6], solution[7], solution[8], solution[9], solution[10], solution[11], solution[12], solution[13], solution[14], solution[15], solution[16], solution[17], solution[18], solution[19], solution[20], solution[21], solution[22], solution[23], solution[24], solution[25], solution[26], solution[27], solution[28], solution[29], solution[30], solution[31], solution[32], solution[33], solution[34], solution[35], solution[36], solution[37], solution[38], solution[39], solution[40], solution[41]);
					if(requestSize < 0) {
					
						// Display message
						cout << endl << "Creating submit request failed" << flush;
						
						// Wait for input to exit
						waitForInputToExit();
					}
					
					// Disable process response from stratum server timer interrupt
					irqDisable(IRQ_TIMER(PROCESS_STRATUM_SERVER_RESPONSE_TIMER));
					
					// Check if connected to stratum server
					if(socketDescriptorUniquePointer) {
					
						// Check if sending submit request to stratum server failed
						if(!sendFull(*socketDescriptorUniquePointer, submitRequest, requestSize)) {
						
							// Disconnect from stratum server
							socketDescriptorUniquePointer.reset();
						}
						
						// Otherwise
						else {
						
							// Display message
							cout << endl << "Solution found!!!" << flush;
							
							// Continue
							continue;
						}
					}
					
					// Enable process response from stratum server timer interrupt
					irqEnable(IRQ_TIMER(PROCESS_STRATUM_SERVER_RESPONSE_TIMER));
				}
				
				// Display message
				cout << endl << "No solution found" << flush;
			}
		}
	}
	
	// Return success
	return EXIT_SUCCESS;
}


// Supporting function implementation

// Wait for input to exit
void waitForInputToExit() {

	// Display message
	cout << endl << "Press A to exit" << flush;
	
	// Loop forever
	while(true) {
	
		// Check if A is pressed
		scanKeys();
		if(keysDown() & KEY_A) {
		
			// Exit failure
			exit(EXIT_FAILURE);
		}
		
		// Wait for vertical blank
		swiWaitForVBlank();
	}
}

// Display mode
void displayModel() {

	// Check if not using Linux
	#ifndef __linux__
	
		// Configure top screen for 3D
		videoSetMode(MODE_0_3D);
		
		// Initialize graphics
		glInit();
		
		// Set viewport
		glViewport(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
		
		// Enable antialiasing
		glEnable(GL_ANTIALIAS);
		
		// Enable textures
		glEnable(GL_TEXTURE_2D);
		
		// Configure rear plane
		glClearPolyID(0);
		glClearColor(4, 4, 4, 31);
		glClearDepth(GL_MAX_DEPTH);
		
		// Map VRAM banks for texture
		vramSetBankA(VRAM_A_TEXTURE);
		vramSetBankB(VRAM_B_TEXTURE);
		
		// Check if creating texture failed
		static int textureDescriptor;
		if(!glGenTextures(1, &textureDescriptor)) {
		
			// Display message
			cout << endl << "Creating texture failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Automatically free texture when done
		static const unique_ptr<int, void(*)(int *)> textureDescriptorUniquePointer(&textureDescriptor, [] ITCM_CODE (int *textureDescriptorPointer) {
		
			// Delete texture
			glDeleteTextures(1, textureDescriptorPointer);
		});
		
		// Check if initializing NitroFS failed
		if(!nitroFSInit(nullptr)) {
		
			// Display message
			cout << endl << "Initializing NitroFS failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if opening model texture file failed
		ifstream modelTextureFile("nitro:/model_texture.bin", ifstream::binary);
		if(!modelTextureFile) {
		
			// Display message
			cout << endl << "Opening model texture file failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if getting model texture size failed
		ifstream::traits_type::pos_type modelTextureFileSize;
		if(!modelTextureFile.seekg(0, ifstream::end) || (modelTextureFileSize = modelTextureFile.tellg()) == -1 || !modelTextureFile.seekg(0)) {
		
			// Close model texture file
			modelTextureFile.close();
			
			// Display message
			cout << endl << "Getting model texture size failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if allocating memory for model texture failed
		uint8_t *modelTexture = new (nothrow) uint8_t[modelTextureFileSize];
		if(!modelTexture) {
		
			// Close model texture file
			modelTextureFile.close();
			
			// Display message
			cout << endl << "Allocating memory for model texture failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if reading model texture file failed
		if(!modelTextureFile.read(reinterpret_cast<char *>(modelTexture), modelTextureFileSize)) {
		
			// Free model texture
			delete [] modelTexture;
			
			// Close model texture file
			modelTextureFile.close();
			
			// Display message
			cout << endl << "Reading model texture file failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Close model texture file
		modelTextureFile.close();
		
		// Check if loading texture failed
		glBindTexture(GL_TEXTURE_2D, textureDescriptor);
		if(!glTexImage2D(GL_TEXTURE_2D, 0, MODEL_TEXTURE_FORMAT, MODEL_TEXTURE_WIDTH, MODEL_TEXTURE_HEIGHT, 0, TEXGEN_OFF, modelTexture)) {
		
			// Free model texture
			delete [] modelTexture;
			
			// Display message
			cout << endl << "Loading texture failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Free model texture
		delete [] modelTexture;
		
		// Map VRAM bank for palette
		vramSetBankE(VRAM_E_TEX_PALETTE);
		
		// Check if opening model palette file failed
		ifstream modelPaletteFile("nitro:/model_palette.bin", ifstream::binary);
		if(!modelPaletteFile) {
		
			// Display message
			cout << endl << "Opening model palette file failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if getting model palette size failed
		ifstream::traits_type::pos_type modelPaletteFileSize;
		if(!modelPaletteFile.seekg(0, ifstream::end) || (modelPaletteFileSize = modelPaletteFile.tellg()) == -1 || !modelPaletteFile.seekg(0)) {
		
			// Close model palette file
			modelPaletteFile.close();
			
			// Display message
			cout << endl << "Getting model palette size failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if allocating memory for model palette failed
		uint16_t *modelPalette = new (nothrow) uint16_t[modelPaletteFileSize / sizeof(uint16_t)];
		if(!modelPalette) {
		
			// Close model palette file
			modelPaletteFile.close();
			
			// Display message
			cout << endl << "Allocating memory for model palette failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Check if reading model palette file failed
		if(!modelPaletteFile.read(reinterpret_cast<char *>(modelPalette), modelPaletteFileSize)) {
		
			// Free model palette
			delete [] modelPalette;
			
			// Close model palette file
			modelPaletteFile.close();
			
			// Display message
			cout << endl << "Reading model palette file failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Close model palette file
		modelPaletteFile.close();
		
		// Load palette
		glColorTableEXT(GL_TEXTURE_2D, 0, modelPaletteFileSize / sizeof(modelPalette[0]), 0, 0, modelPalette);
		
		// Free model palette
		delete [] modelPalette;
		
		// Configure material
		glMaterialf(GL_AMBIENT, RGB15(9, 7, 7));
		glMaterialf(GL_DIFFUSE, RGB15(31, 31, 31));
		glMaterialf(GL_SPECULAR, ARGB16(1, 1, 1, 1));
		glMaterialf(GL_EMISSION, RGB15(0, 0, 0));
		glMaterialShinyness();
		
		// Configure light
		glLight(0, RGB15(31, 31, 31), floattov10(-0.15), floattov10(-0.45), floattov10(-0.4));
		
		// Configure projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspectivef32(degreesToAngle(45), floattof32(static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT), floattof32(0.1), floattof32(10));
		
		// Configure view matrix
		gluLookAtf32(floattof32(0), floattof32(0), floattof32(1.6), floattof32(0), floattof32(0), floattof32(0), floattof32(0), floattof32(1), floattof32(0));
		
		// Save view matrix
		glStoreMatrix(0);
		
		// Set model's ID, make it opaque, cull its back faces, and enable lighting on it
		glPolyFmt(POLY_ID(1) | POLY_ALPHA(31) | POLY_CULL_BACK | POLY_FORMAT_LIGHT0);
		
		// Set vertical blank interrupt handler
		static int modelRotation = degreesToAngle(90);
		irqSet(IRQ_VBLANK, [] ITCM_CODE () {
		
			// Configure model matrix
			glRestoreMatrix(0);
			glRotateYi(modelRotation);
			
			// Start drawing triangles
			glBegin(GL_TRIANGLES);
			
			// Go through all of model's vertices
			for(size_t i = 0; i < NUMBER_OF_MODEL_VERTICES; ++i) {
			
				// Draw vertex
				glNormal(modelVertices[i][0].normal);
				glTexCoord2t16(modelVertices[i][1].textureCoordinate, modelVertices[i][2].textureCoordinate);
				glVertex3v16(modelVertices[i][3].position, modelVertices[i][4].position, modelVertices[i][5].position);
			}
			
			// Finish drawing triangles
			glEnd();
			
			// Update model rotation
			modelRotation += degreesToAngle(45) / FRAMES_PER_SECOND;
			
			// Update screen
			glFlush(0);
		});
	#endif
}

// Connect to stratum server
unique_ptr<int, void(*)(int *)> connectToStratumServer() {

	// Check if opening stratum settings file failed
	ifstream stratumFile(STRATUM_SETTINGS_FILE, ifstream::binary);
	if(!stratumFile) {
	
		// Display message
		cout << endl << "Opening " STRATUM_SETTINGS_FILE " failed" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Check if reading stratum server address from stratum settings file failed
	char stratumAddress[STRATUM_SETTINGS_FILE_MAX_LINE_SIZE];
	if(!stratumFile.getline(stratumAddress, sizeof(stratumAddress))) {
	
		// Close stratum settings file
		stratumFile.close();
		
		// Display message
		cout << endl << "Reading " STRATUM_SETTINGS_FILE " failed" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Go through all characters in stratum server address
	for(streamsize i = 0; i < stratumFile.gcount() - static_cast<streamsize>(sizeof('\0')); ++i) {
	
		// Check if character isn't a printable or newline character
		if(!isprint(stratumAddress[i]) && stratumAddress[i] != '\n' && (stratumAddress[i] != '\r' || stratumAddress[i + sizeof('\r')] != '\n')) {
		
			// Close stratum settings file
			stratumFile.close();
			
			// Display message
			cout << endl << "Stratum server address is invalid" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
	}
	
	// Check if stratum server address doesn't contain an address or a port
	char *stratumPortIndex = strchr(stratumAddress, ':');
	if(!stratumPortIndex || stratumPortIndex == stratumAddress || !isdigit(stratumPortIndex[sizeof(':')]) || (stratumPortIndex[sizeof(':')] == '0' && isdigit(stratumPortIndex[sizeof(':') + sizeof('0')]))) {
	
		// Close stratum settings file
		stratumFile.close();
		
		// Display message
		cout << endl << "Stratum server address is invalid" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Check if stratum server address's port is invalid
	char *stratumPortEnd;
	const unsigned long stratumPort = strtoul(&stratumPortIndex[sizeof(':')], &stratumPortEnd, 10);
	if(!stratumPort || stratumPort > UINT16_MAX || (*stratumPortEnd && *stratumPortEnd != '\n' && *stratumPortEnd != '\r')) {
	
		// Close stratum settings file
		stratumFile.close();
		
		// Display message
		cout << endl << "Stratum server address is invalid" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Null terminate stratum server address
	*stratumPortIndex = '\0';
	
	// Check if getting if stratum settings file has another line failed
	const bool anotherLineExists = stratumFile.peek() != ifstream::traits_type::eof();
	if(!stratumFile) {
	
		// Close stratum settings file
		stratumFile.close();
		
		// Display message
		cout << endl << "Reading " STRATUM_SETTINGS_FILE " failed" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Check if stratum settings file has another line
	char stratumUsername[STRATUM_SETTINGS_FILE_MAX_LINE_SIZE] = {'\0'};
	if(anotherLineExists) {
	
		// Check if reading stratum server username from stratum settings file failed
		if(!stratumFile.getline(stratumUsername, sizeof(stratumUsername))) {
		
			// Close stratum settings file
			stratumFile.close();
			
			// Display message
			cout << endl << "Reading " STRATUM_SETTINGS_FILE " failed" << flush;
			
			// Wait for input to exit
			waitForInputToExit();
		}
		
		// Go through all characters in stratum server username
		for(streamsize i = 0; i < stratumFile.gcount() - static_cast<streamsize>(sizeof('\0')); ++i) {
		
			// Check if character isn't a printable or newline character or requires being escaped when encodes as JSON
			if((!isprint(stratumUsername[i]) && stratumUsername[i] != '\n' && (stratumUsername[i] != '\r' || stratumUsername[i + sizeof('\r')] != '\n')) || stratumUsername[i] == '"' || stratumUsername[i] == '\\') {
			
				// Close stratum settings file
				stratumFile.close();
				
				// Display message
				cout << endl << "Stratum server username is invalid" << flush;
				
				// Wait for input to exit
				waitForInputToExit();
			}
		}
		
		// Check if stratum server username ends with a newline
		char *stratumUsernameEnd = strpbrk(stratumUsername, "\r\n");
		if(stratumUsernameEnd) {
		
			// Remove newline from stratum server username
			*stratumUsernameEnd = '\0';
		}
	}
	
	// Close stratum settings file
	stratumFile.close();
	
	// Check if not connected to network
	static bool connectedToNetwork = false;
	if(!connectedToNetwork) {
	
		// Display message
		cout << endl << "Connecting to network" << flush;
		
		// Check if connecting to network failed
		if(!Wifi_InitDefault(WFC_CONNECT)) {
		
			// Display message
			cout << endl << "Connecting to network failed" << flush;
			
			// Return failure
			return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
		}
		
		// Set connected to network to true
		connectedToNetwork = true;
		
		// Display message
		cout << endl << "Connected to network" << flush;
	}
	
	// Display message
	cout << endl << "Connecting to stratum server at " << stratumAddress << ':' << stratumPort << flush;
	
	// Check if getting stratum server info failed
	const hostent *stratumServerInfo = gethostbyname(stratumAddress);
	if(!stratumServerInfo) {
	
		// Display message
		cout << endl << "Getting IP address for stratum server failed" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Loop while socket doesn't exist
	static int socketDescriptor;
	do {
	
		// Check if creating socket failed
		socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
		if(socketDescriptor == -1) {
		
			// Check if creating socket failed for being out of memory
			if(errno == ENOMEM) {
			
				// Free socket resources
				Wifi_Timer(MILLISECONDS_IN_A_SECOND);
			}
			
			// Otherwise
			else {
			
				// Display message
				cout << endl << "Creating socket failed" << flush;
				
				// Wait for input to exit
				waitForInputToExit();
			}
		}
		
	} while(socketDescriptor == -1);
	
	// Check if connecting to stratum server failed
	const sockaddr_in serverAddress = {
	
		// Family
		.sin_family = AF_INET,
		
		// Port
		.sin_port = htons(stratumPort),
		
		// Address
		.sin_addr = *reinterpret_cast<const in_addr *>(stratumServerInfo->h_addr_list[0])
	};
	if(connect(socketDescriptor, reinterpret_cast<const sockaddr *>(&serverAddress), sizeof(serverAddress))) {
	
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Connecting to stratum server failed" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Display message
	cout << endl << "Connected to stratum server" << flush;
	
	// Check if stratum server username exists
	if(stratumUsername[0]) {
	
		// Display message
		cout << endl << "Logging into stratum server with username " << stratumUsername << flush;
	}
	
	// Otherwise
	else {
	
		// Display message
		cout << endl << "Logging into stratum server without username" << flush;
	}
	
	// Check if sending login request to stratum server failed
	if(!sendFull(socketDescriptor, "{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"login\",\"params\":{\"login\":\"", sizeof("{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"login\",\"params\":{\"login\":\"") - sizeof('\0')) || (stratumUsername[0] && !sendFull(socketDescriptor, stratumUsername, strlen(stratumUsername))) || !sendFull(socketDescriptor, "\",\"pass\":\"\",\"agent\":\"MWC DS Miner\"}}\n", sizeof("\",\"pass\":\"\",\"agent\":\"MWC DS Miner\"}}\n") - sizeof('\0'))) {
	
		// Shutdown socket
		shutdown(socketDescriptor, SHUT_RDWR);
		
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Logging into stratum server failed" << flush;
		
		// Display message
		cout << endl << "Disconnecting from stratum server" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Check if receiving response from stratum server failed
	char response[STRATUM_SERVER_RESPONSE_BUFFER_SIZE];
	if(!receiveFull(socketDescriptor, response, sizeof(response))) {
	
		// Shutdown socket
		shutdown(socketDescriptor, SHUT_RDWR);
		
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Logging into stratum server failed" << flush;
		
		// Display message
		cout << endl << "Disconnecting from stratum server" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Check if logging into stratum server failed
	if(!strstr(response, "\"error\":null")) {
	
		// Shutdown socket
		shutdown(socketDescriptor, SHUT_RDWR);
		
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Logging into stratum server failed" << flush;
		
		// Display message
		cout << endl << "Disconnecting from stratum server" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Display message
	cout << endl << "Logged into stratum server" << flush;
	
	// Check if sending get job template request to stratum server failed
	if(!sendFull(socketDescriptor, "{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"getjobtemplate\",\"params\":null}\n", sizeof("{\"id\":\"1\",\"jsonrpc\":\"2.0\",\"method\":\"getjobtemplate\",\"params\":null}\n") - sizeof('\0'))) {
	
		// Shutdown socket
		shutdown(socketDescriptor, SHUT_RDWR);
		
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Getting job from stratum server failed" << flush;
		
		// Display message
		cout << endl << "Disconnecting from stratum server" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Check if receiving response from stratum server failed
	if(!receiveFull(socketDescriptor, response, sizeof(response))) {
	
		// Shutdown socket
		shutdown(socketDescriptor, SHUT_RDWR);
		
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Getting job from stratum server failed" << flush;
		
		// Display message
		cout << endl << "Disconnecting from stratum server" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Check if getting job from response failed
	if(!processStratumServerResponse(response)) {
	
		// Shutdown socket
		shutdown(socketDescriptor, SHUT_RDWR);
		
		// Close socket
		closesocket(socketDescriptor);
		
		// Display message
		cout << endl << "Getting job from stratum server failed" << flush;
		
		// Display message
		cout << endl << "Disconnecting from stratum server" << flush;
		
		// Return failure
		return unique_ptr<int, void(*)(int *)>(nullptr, [] ITCM_CODE (int *) {});
	}
	
	// Return socket that automatically frees itself when done
	return unique_ptr<int, void(*)(int *)>(&socketDescriptor, [] ITCM_CODE (int *socketDescriptorPointer) {
	
		// Shutdown socket
		shutdown(*socketDescriptorPointer, SHUT_RDWR);
		
		// Close socket
		closesocket(*socketDescriptorPointer);
	});
}

// Process stratum server response
bool processStratumServerResponse(char response[STRATUM_SERVER_RESPONSE_BUFFER_SIZE]) {

	// Initialize job height
	unsigned long long jobHeight;
	
	// Initialize job ID
	unsigned long long jobId;
	
	// Initialize job header
	uint8_t jobHeader[HEADER_SIZE];
	
	// Set job found to false
	bool jobFound = false;
	
	// Go through all complete parts of the response
	for(char *partStart = response, *partEnd = strchr(partStart, '\n'); partStart && partEnd; partStart = &partEnd[sizeof('\n')], partEnd = strchr(partStart, '\n')) {
	
		// Null terminate the part
		*partEnd = '\0';
		
		// Check if getting part's method was successful
		const char *method = strstr(partStart, "\"method\":");
		if(method) {
		
			// Check if method is get job template or job
			if(!strncmp(&method[sizeof("\"method\":") - sizeof('\0')], "\"getjobtemplate\"", sizeof("\"getjobtemplate\"") - sizeof('\0')) || !strncmp(&method[sizeof("\"method\":") - sizeof('\0')], "\"job\"", sizeof("\"job\"") - sizeof('\0'))) {
			
				// Set job found to false
				jobFound = false;
				
				// Check if getting job was successful
				if(strstr(partStart, "\"error\":null") || !strncmp(&method[sizeof("\"method\":") - sizeof('\0')], "\"job\"", sizeof("\"job\"") - sizeof('\0'))) {
				
					// Check if getting job height was successful
					const char *height = strstr(partStart, "\"height\":");
					if(height) {
					
						// Check if getting job height was successful
						char *end;
						errno = 0;
						jobHeight = strtoull(&height[sizeof("\"height\":") - sizeof('\0')], &end, 10);
						if(end != &height[sizeof("\"height\":") - sizeof('\0')] && isdigit(height[sizeof("\"height\":") - sizeof('\0')]) && (height[sizeof("\"height\":") - sizeof('\0')] != '0' || !isdigit(height[sizeof("\"height\":") - sizeof('\0') + sizeof('0')])) && !errno && jobHeight && jobHeight <= UINT64_MAX) {
						
							// Check if getting job ID was successful
							const char *id = strstr(partStart, "\"job_id\":");
							if(id) {
							
								// Check if getting job ID was successful
								errno = 0;
								jobId = strtoull(&id[sizeof("\"job_id\":") - sizeof('\0')], &end, 10);
								if(end != &id[sizeof("\"job_id\":") - sizeof('\0')] && isdigit(id[sizeof("\"job_id\":") - sizeof('\0')]) && (id[sizeof("\"job_id\":") - sizeof('\0')] != '0' || !isdigit(id[sizeof("\"job_id\":") - sizeof('\0') + sizeof('0')])) && !errno && jobId <= UINT64_MAX) {
								
									// Check if getting job pre-proof of work was successful
									const char *preProofOfWork = strstr(partStart, "\"pre_pow\":\"");
									if(preProofOfWork) {
									
										// Reset job header
										memset(jobHeader, 0, sizeof(jobHeader));
										
										// Go through all hex characters in the job pre-proof of work
										for(const char *i = &preProofOfWork[sizeof("\"pre_pow\":\"") - sizeof('\0')]; isxdigit(*i) && !isupper(*i); ++i) {
										
											// Check if job pre-proof of work is too long
											if((i - &preProofOfWork[sizeof("\"pre_pow\":\"") - sizeof('\0')]) / 2 == sizeof(jobHeader)) {
											
												// Break
												break;
											}
											
											// Set character in job header
											jobHeader[(i - &preProofOfWork[sizeof("\"pre_pow\":\"") - sizeof('\0')]) / 2] |= ((i - &preProofOfWork[sizeof("\"pre_pow\":\"") - sizeof('\0')]) % 2) ? ((*i - ((*i > '9') ? '0' + 'a' - '9' - 1 : '0')) & 0xF) : ((*i - ((*i > '9') ? '0' + 'a' - '9' - 1 : '0')) << 4);
											
											// Check if next character terminates the job pre-proof of work and the job pre-proof of work is the correct size
											if(i[1] == '"' && i - &preProofOfWork[sizeof("\"pre_pow\":\"") - sizeof('\0')] == sizeof(jobHeader) * 2 - 1) {
											
												// Set job found to true
												jobFound = true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	// Check if a job was found
	if(jobFound) {
	
		// Set next job height to job height
		nextJobHeight = jobHeight;
		
		// Set next job ID to job ID
		nextJobId = jobId;
		
		// Set next job header to job header
		memcpy(nextJobHeader, jobHeader, sizeof(jobHeader));
		
		// Set new next job to true
		newNextJob = true;
		
		// Return true
		return true;
	}
	
	// Return false
	return false;
}

// Send full
bool sendFull(const int socketDescriptor, const char *data, size_t size) {

	// Check if setting socket as non-blocking failed
	int nonBlocking = 1;
	if(ioctl(socketDescriptor, FIONBIO, &nonBlocking)) {
	
		// Return false
		return false;
	}
	
	// Start CPU timing
	cpuStartTiming(SOCKET_TIMEOUT_TIMER);
	
	// Loop while there's data to send
	while(size) {
	
		// Check if send timeout occurred
		if(timerTicks2msec(cpuGetTiming()) >= SEND_TIMEOUT_MILLISECONDS) {
		
			// Stop CPU timing
			cpuEndTiming();
			
			// Set socket as blocking
			nonBlocking = 0;
			ioctl(socketDescriptor, FIONBIO, &nonBlocking);
			
			// Return false
			return false;
		}
		
		// Check if sending remaining data failed
		const int sent = send(socketDescriptor, data, size, 0);
		if(sent == -1) {
		
			// Check if sending failed not because it would have blocked
			if(errno != EWOULDBLOCK) {
			
				// Stop CPU timing
				cpuEndTiming();
				
				// Set socket as blocking
				nonBlocking = 0;
				ioctl(socketDescriptor, FIONBIO, &nonBlocking);
				
				// Return false
				return false;
			}
		}
		
		// Otherwise
		else {
		
			// Update remaining data
			data += sent;
			size -= sent;
		}
	}
	
	// Stop CPU timing
	cpuEndTiming();
	
	// Check if setting socket as blocking failed
	nonBlocking = 0;
	if(ioctl(socketDescriptor, FIONBIO, &nonBlocking)) {
	
		// Return false
		return false;
	}
	
	// Return true
	return true;
}

// Receive full
bool receiveFull(const int socketDescriptor, char *data, const size_t size) {

	// Check if setting socket as non-blocking failed
	int nonBlocking = 1;
	if(ioctl(socketDescriptor, FIONBIO, &nonBlocking)) {
	
		// Return false
		return false;
	}
	
	// Start CPU timing
	cpuStartTiming(SOCKET_TIMEOUT_TIMER);
	
	// Loop until full message is received
	int received;
	do {
	
		// Check if receive timeout occurred
		if(timerTicks2msec(cpuGetTiming()) >= RECEIVE_TIMEOUT_MILLISECONDS) {
		
			// Stop CPU timing
			cpuEndTiming();
			
			// Set socket as blocking
			nonBlocking = 0;
			ioctl(socketDescriptor, FIONBIO, &nonBlocking);
			
			// Return false
			return false;
		}
		
		// Check if receiving data failed not because it would have blocked
		received = recv(socketDescriptor, data, size - sizeof('\0'), MSG_PEEK);
		if((received == -1 && errno != EWOULDBLOCK) || !received || (received != -1 && static_cast<size_t>(received) == size - sizeof('\0'))) {
		
			// Stop CPU timing
			cpuEndTiming();
			
			// Set socket as blocking
			nonBlocking = 0;
			ioctl(socketDescriptor, FIONBIO, &nonBlocking);
			
			// Return false
			return false;
		}
	
	} while(received == -1 || !memchr(data, '\n', received));
	
	// Stop CPU timing
	cpuEndTiming();
	
	// Check if receiving data failed
	received = recv(socketDescriptor, data, size - sizeof('\0'), 0);
	if(received <= 0) {
	
		// Set socket as blocking
		nonBlocking = 0;
		ioctl(socketDescriptor, FIONBIO, &nonBlocking);
		
		// Return false
		return false;
	}
	
	// Null terminate message
	data[received] = '\0';
	
	// Check if setting socket as blocking failed
	nonBlocking = 0;
	if(ioctl(socketDescriptor, FIONBIO, &nonBlocking)) {
	
		// Return false
		return false;
	}
	
	// Return true
	return true;
}

// Mine job
bool mineJob(const uint8_t jobHeader[HEADER_SIZE], const uint64_t jobNonce, volatile uint16_t *expansionRam, uint32_t solution[SOLUTION_SIZE]) {
	
	// Get SipHash keys from job header and nonce
	uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) sipHashKeys;
	blake2b(jobHeader, jobNonce, sipHashKeys);
	
	// Check if creating edges bitmap file failed
	fstream edgesBitmapFile(EDGES_BITMAP_FILE, fstream::in | fstream::out | fstream::binary | fstream::trunc);
	if(!edgesBitmapFile) {
	
		// Display message
		cout << endl << "Creating " EDGES_BITMAP_FILE " failed" << flush;
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Check if trimming edges failed
	if(!trimEdges(sipHashKeys, edgesBitmapFile, expansionRam)) {
	
		// Close edges bitmap file
		edgesBitmapFile.close();
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Check if searching remaining edges failed
	solution[1] = 0;
	if(!searchRemainingEdges(sipHashKeys, edgesBitmapFile, solution)) {
	
		// Close edges bitmap file
		edgesBitmapFile.close();
		
		// Wait for input to exit
		waitForInputToExit();
	}
	
	// Close edges bitmap file
	edgesBitmapFile.close();
	
	// Return if a solution was found
	return solution[1];
}

// Trim edges
bool trimEdges(const uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &sipHashKeys, fstream &edgesBitmapFile, volatile uint16_t *expansionRam) {

	// Display message
	cout << endl << "Trimming edges 0%" << flush;
	
	// Set nodes bitmap part to RAM expansion pak's RAM if available
	volatile uint16_t *nodesBitmapPart = expansionRam;
	const size_t nodesBitmapPartSize = expansionRam ? ram_size() : LOCAL_RAM_SIZE;
	const int divideByNodesBitmapPartSizeShiftRight = bit_width(nodesBitmapPartSize) - 1;
	const int moduloByNodesBitmapPartSizeBitsAnd = nodesBitmapPartSize * BITS_IN_A_BYTE - 1;
	
	// Check if not using a RAM expansion pak
	if(!expansionRam) {
	
		// Check if creating nodes bitmap part failed
		nodesBitmapPart = reinterpret_cast<volatile uint16_t *>(alloca(LOCAL_RAM_SIZE));
		if(nodesBitmapPart < MAINRAM16 + LOCAL_RAM_SIZE + SECONDARY_LOCAL_RAM_SIZE) {
		
			// Display message
			cout << endl << "Allocating memory failed" << flush;
			
			// Return false
			return false;
		}
	}
	
	// Check if creating edges bitmap part failed
	const size_t edgesBitmapPartSize = expansionRam ? LOCAL_RAM_SIZE : SECONDARY_LOCAL_RAM_SIZE;
	const int divideByEdgesBitmapPartSizeShiftRight = bit_width(edgesBitmapPartSize) - 1;
	uint32_t *edgesBitmapPart = reinterpret_cast<uint32_t *>(alloca(edgesBitmapPartSize));
	if(edgesBitmapPart < MAINRAM32 + edgesBitmapPartSize) {
	
		// Display message
		cout << endl << "Allocating memory failed" << flush;
		
		// Return false
		return false;
	}
	
	// Go through all edges bitmap parts
	for(size_t i = 0; i < BYTES_PER_BITMAP >> divideByEdgesBitmapPartSizeShiftRight; ++i) {
	
		// Enable all edges in edges bitmap part
		memset(edgesBitmapPart, UINT8_MAX, edgesBitmapPartSize);
		
		// Check if writing edges bitmap part to edges bitmap file failed
		if(!edgesBitmapFile.write(reinterpret_cast<const char *>(edgesBitmapPart), edgesBitmapPartSize)) {
		
			// Display message
			cout << endl << "Writing to " EDGES_BITMAP_FILE " failed" << flush;
			
			// Return false
			return false;
		}
	}
	
	// Go through all trimming rounds
	int lastPercentComplete = 0;
	for(int i = 0; i < TRIMMING_ROUNDS; ++i) {
	
		// Check if percent complete changed
		const int percentComplete = i * 100 / TRIMMING_ROUNDS;
		if(lastPercentComplete != percentComplete) {
		
			// Update last percent complete
			lastPercentComplete = percentComplete;
			
			// Display message
			iprintf("\x1b[%d;0HTrimming edges %d%%", console->cursorY, percentComplete);
			cout << flush;
		}
		
		// Go through all nodes bitmap parts
		for(size_t j = 0; j < BYTES_PER_BITMAP >> divideByNodesBitmapPartSizeShiftRight; ++j) {
		
			// Clear nodes bitmap part
			memset(const_cast<uint16_t *>(nodesBitmapPart), 0, nodesBitmapPartSize);
			
			// Check if going to the beginning of edges bitmap file failed
			if(!edgesBitmapFile.seekg(0)) {
			
				// Display message
				cout << endl << "Reading from " EDGES_BITMAP_FILE " failed" << flush;
				
				// Return false
				return false;
			}
			
			// Go through all edges bitmap parts
			for(size_t k = 0; k < BYTES_PER_BITMAP >> divideByEdgesBitmapPartSizeShiftRight; ++k) {
			
				// Check if reading edges bitmap part from edges bitmap file
				if(!edgesBitmapFile.read(reinterpret_cast<char *>(edgesBitmapPart), edgesBitmapPartSize)) {
				
					// Display message
					cout << endl << "Reading from " EDGES_BITMAP_FILE " failed" << flush;
					
					// Return false
					return false;
				}
				
				// Go through all groups of edges in the edges bitmap part
				for(size_t l = 0; l < edgesBitmapPartSize / sizeof(edgesBitmapPart[0]); ++l) {
				
					// Go through all enabled edges in the group
					uint32_t edgeGroupBits = edgesBitmapPart[l];
					for(int currentBitIndex = __builtin_ffs(edgeGroupBits), previousBitIndex = 0; currentBitIndex; edgeGroupBits >>= currentBitIndex, previousBitIndex += currentBitIndex, currentBitIndex = __builtin_ffs(edgeGroupBits)) {
					
						// Get edge's index
						const uint32_t edgeIndex = ((k * BITS_IN_A_BYTE) << divideByEdgesBitmapPartSizeShiftRight) + l * (sizeof(edgesBitmapPart[0]) * BITS_IN_A_BYTE) + currentBitIndex - 1 + previousBitIndex;
						
						// Get edge's node on current partition
						const uint32_t node = sipHash24(sipHashKeys, (edgeIndex * 2) | (i % 2)) & NODE_MASK;
						
						// Check if node belongs to the nodes bitmap part
						if(((node / BITS_IN_A_BYTE) >> divideByNodesBitmapPartSizeShiftRight) == j) {
						
							// Enable node in nodes bitmap part
							nodesBitmapPart[(node & moduloByNodesBitmapPartSizeBitsAnd) / (sizeof(nodesBitmapPart[0]) * BITS_IN_A_BYTE)] |= 1 << ((node & moduloByNodesBitmapPartSizeBitsAnd) % (sizeof(nodesBitmapPart[0]) * BITS_IN_A_BYTE));
						}
						
						// Check if shifting by the entire group of bits
						if(currentBitIndex == sizeof(edgeGroupBits) * BITS_IN_A_BYTE) {
						
							// Break
							break;
						}
					}
				}
			}
			
			// Check if going to the beginning of edges bitmap file failed
			if(!edgesBitmapFile.seekg(0)) {
			
				// Display message
				cout << endl << "Reading from " EDGES_BITMAP_FILE " failed" << flush;
				
				// Return false
				return false;
			}
			
			// Go through all edges bitmap parts
			for(size_t k = 0; k < BYTES_PER_BITMAP >> divideByEdgesBitmapPartSizeShiftRight; ++k) {
			
				// Check if reading edges bitmap part from edges bitmap file
				const fstream::traits_type::pos_type edgesBitmapFilePosition = edgesBitmapFile.tellp();
				if(edgesBitmapFilePosition == -1 || !edgesBitmapFile.read(reinterpret_cast<char *>(edgesBitmapPart), edgesBitmapPartSize) || !edgesBitmapFile.seekp(edgesBitmapFilePosition)) {
				
					// Display message
					cout << endl << "Reading from " EDGES_BITMAP_FILE " failed" << flush;
					
					// Return false
					return false;
				}
				
				// Go through all groups of edges in the edges bitmap part
				for(size_t l = 0; l < edgesBitmapPartSize / sizeof(edgesBitmapPart[0]); ++l) {
				
					// Go through all enabled edges in the group
					uint32_t edgeGroupBits = edgesBitmapPart[l];
					for(int currentBitIndex = __builtin_ffs(edgeGroupBits), previousBitIndex = 0; currentBitIndex; edgeGroupBits >>= currentBitIndex, previousBitIndex += currentBitIndex, currentBitIndex = __builtin_ffs(edgeGroupBits)) {
					
						// Get edge's index
						const uint32_t edgeIndex = ((k * BITS_IN_A_BYTE) << divideByEdgesBitmapPartSizeShiftRight) + l * (sizeof(edgesBitmapPart[0]) * BITS_IN_A_BYTE) + currentBitIndex - 1 + previousBitIndex;
						
						// Get edge's node on current partition
						const uint32_t node = sipHash24(sipHashKeys, (edgeIndex * 2) | (i % 2)) & NODE_MASK;
						
						// Check if node belongs to the nodes bitmap part
						if(((node / BITS_IN_A_BYTE) >> divideByNodesBitmapPartSizeShiftRight) == j) {
						
							// Check if node's pair is disabled in nodes bitmap part
							if(!(nodesBitmapPart[((node & moduloByNodesBitmapPartSizeBitsAnd) ^ 1) / (sizeof(nodesBitmapPart[0]) * BITS_IN_A_BYTE)] & (1 << (((node & moduloByNodesBitmapPartSizeBitsAnd) ^ 1) % (sizeof(nodesBitmapPart[0]) * BITS_IN_A_BYTE))))) {
							
								// Disable edge in edges bitmap part
								edgesBitmapPart[l] ^= 1 << (edgeIndex % (sizeof(edgesBitmapPart[0]) * BITS_IN_A_BYTE));
							}
						}
						
						// Check if shifting by the entire group of bits
						if(currentBitIndex == sizeof(edgeGroupBits) * BITS_IN_A_BYTE) {
						
							// Break
							break;
						}
					}
				}
				
				// Check if writing edges bitmap part to edges bitmap file failed
				if(!edgesBitmapFile.write(reinterpret_cast<const char *>(edgesBitmapPart), edgesBitmapPartSize)) {
				
					// Display message
					cout << endl << "Writing to " EDGES_BITMAP_FILE " failed" << flush;
					
					// Return false
					return false;
				}
			}
		}
	}
	
	// Display message
	iprintf("\x1b[%d;0HTrimming edges 100%%", console->cursorY);
	cout << flush;
	
	// Return true
	return true;
}

// Search remaining edges
bool searchRemainingEdges(const uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &sipHashKeys, fstream &edgesBitmapFile, uint32_t solution[SOLUTION_SIZE]) {

	// Display message
	cout << endl << "Searching remaining edges 0%" << flush;
	
	// Check if going to the beginning of edges bitmap file failed
	if(!edgesBitmapFile.seekg(0)) {
	
		// Display message
		cout << endl << "Reading from " EDGES_BITMAP_FILE " failed" << flush;
		
		// Return false
		return false;
	}
	
	// Create node connections
	CuckatooNodeConnection nodeConnections[MAX_NUMBER_OF_EDGES_AFTER_TRIMMING * 2];
	HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> newestUNodesConnection;
	HashTable<CuckatooNodeConnection, MAX_NUMBER_OF_EDGES_AFTER_TRIMMING> newestVNodesConnection;
	
	// Go through all groups of edges in the edges bitmap file
	uint32_t numberOfEdges = 0;
	int lastPercentComplete = 0;
	for(size_t i = 0; i < BYTES_PER_BITMAP / sizeof(uint32_t); ++i) {
	
		// Check if percent complete changed
		const int percentComplete = i * 100 / (BYTES_PER_BITMAP / sizeof(uint32_t));
		if(lastPercentComplete != percentComplete) {
		
			// Update last percent complete
			lastPercentComplete = percentComplete;
			
			// Display message
			iprintf("\x1b[%d;0HSearching remaining edges %d%%", console->cursorY, percentComplete);
			cout << flush;
		}
		
		// Check if reading group of edges from edges bitmap file failed
		uint32_t edgeGroupBits;
		if(!edgesBitmapFile.read(reinterpret_cast<char *>(&edgeGroupBits), sizeof(edgeGroupBits))) {
		
			// Display message
			cout << endl << "Reading from " EDGES_BITMAP_FILE " failed" << flush;
			
			// Return false
			return false;
		}
		
		// Go through all enabled edges in the group
		for(int currentBitIndex = __builtin_ffs(edgeGroupBits), previousBitIndex = 0; currentBitIndex; edgeGroupBits >>= currentBitIndex, previousBitIndex += currentBitIndex, currentBitIndex = __builtin_ffs(edgeGroupBits)) {
		
			// Check if the max number of edges have been searched
			if(numberOfEdges == MAX_NUMBER_OF_EDGES_AFTER_TRIMMING) {
			
				// Display message
				cout << endl << "Too many edges remain. Some edges won't be searched" << flush;
				
				// Return true
				return true;
			}
			
			// Get edge's index
			const uint32_t edgeIndex = i * (sizeof(edgeGroupBits) * BITS_IN_A_BYTE) + currentBitIndex - 1 + previousBitIndex;
			
			// Get edge's nodes on both partitions
			const uint32_t uNode = sipHash24(sipHashKeys, edgeIndex * 2) & NODE_MASK;
			const uint32_t vNode = sipHash24(sipHashKeys, (edgeIndex * 2) | 1) & NODE_MASK;
			
			// Check if solution was found with adding the edge to the graph
			if(getCuckatooSolution(edgeIndex, uNode, vNode, &nodeConnections[numberOfEdges * 2], newestUNodesConnection, newestVNodesConnection, solution)) {
			
				// Return true
				return true;
			}
			
			// Increment number of edges
			++numberOfEdges;
			
			// Check if shifting by the entire group of bits
			if(currentBitIndex == sizeof(edgeGroupBits) * BITS_IN_A_BYTE) {
			
				// Break
				break;
			}
		}
	}
	
	// Display message
	iprintf("\x1b[%d;0HSearching remaining edges 100%%", console->cursorY);
	cout << flush;
	
	// Return true
	return true;
}
