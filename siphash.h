// Header guard
#ifndef SIPHASH_H
#define SIPHASH_H


// Header files
using namespace std;


// Constants

// SipHash keys size
#define SIPHASH_KEYS_SIZE 4

// SipRound rotation
#define SIP_ROUND_ROTATION 21


// Function prototypes

// SipHash-2-4
ITCM_CODE static inline uint32_t sipHash24(const uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &sipHashKeys, const uint32_t nonce);

// SipRound
ITCM_CODE static inline void sipRound(uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &state);


// Supporting function implementation

// SipHash-2-4
uint32_t sipHash24(const uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &sipHashKeys, const uint32_t nonce) {

	// Perform hash using SipHash keys and nonce
	uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) state = sipHashKeys;
	state[3] ^= nonce;
	sipRound(state);
	sipRound(state);
	state[0] ^= nonce;
	state[2] ^= 255;
	sipRound(state);
	sipRound(state);
	sipRound(state);
	sipRound(state);
	
	// Return result from state
	return state[0] ^ state[1] ^ state[2] ^ state[3];
}

// SipRound
void sipRound(uint64_t __attribute__((vector_size(sizeof(uint64_t) * SIPHASH_KEYS_SIZE))) &state) {

	// Perform SipRound on state
	state[0] += state[1];
	state[2] += state[3];
	state[1] = rotl(state[1], 13);
	state[3] = rotl(state[3], 16);
	state[1] ^= state[0];
	state[3] ^= state[2];
	state[0] = rotl(state[0], 32);
	state[2] += state[1];
	state[0] += state[3];
	state[1] = rotl(state[1], 17);
	state[3] = rotl(state[3], SIP_ROUND_ROTATION);
	state[1] ^= state[2];
	state[3] ^= state[0];
	state[2] = rotl(state[2], 32);
}


#endif
