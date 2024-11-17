// Header guard
#ifndef HASH_TABLE_H
#define HASH_TABLE_H


// Header files
using namespace std;


// Classes

// Hash table class
template<typename ValueType, const uint32_t size> class HashTable final {

	// Public
	public:
	
		// Constructor
		inline explicit HashTable();
		
		// Set unique
		ITCM_CODE inline void setUnique(const uint32_t key, const ValueType *value);
		
		// Set unique and get index
		ITCM_CODE inline uint32_t setUniqueAndGetIndex(const uint32_t key, const ValueType *value);
		
		// Replace
		ITCM_CODE inline const ValueType *replace(const uint32_t key, const ValueType *value);
		
		// Remove most recent set unique
		ITCM_CODE inline void removeMostRecentSetUique(const uint32_t index);
		
		// Clear
		ITCM_CODE inline void clear();
		
		// Contains
		ITCM_CODE inline bool contains(const uint32_t key) const;
		
		// Get
		ITCM_CODE inline const ValueType *get(const uint32_t key) const;
		
		// Get values
		ITCM_CODE inline void getValues(ValueType *values) const;
	
	// Private
	private:
	
		// Hash table entry structure
		struct HashTableEntry {
		
			// Key
			uint32_t key;
			
			// Value
			const ValueType *value;
		};
		
		// Entries
		HashTableEntry entries[bit_ceil(size + 1)];
};


// Supporting function implementation

// Constructor
template<typename ValueType, const uint32_t size> HashTable<ValueType, size>::HashTable() {

	// Throw error is size is invalid
	static_assert(size <= bit_ceil(UINT32_MAX >> 1) - 1, "Hash table's size is invalid");
	
	// Clear entries
	memset(entries, 0, sizeof(entries));
}

// Set unique
template<typename ValueType, const uint32_t size> void HashTable<ValueType, size>::setUnique(const uint32_t key, const ValueType *value) {

	// Get key's index
	uint32_t index = key % (sizeof(entries) / sizeof(entries[0]));
	
	// Loop while entry at index exists
	while(entries[index].value) {
	
		// Check if index isn't for the last entry
		if(index != (sizeof(entries) / sizeof(entries[0])) - 1) {
		
			// Increment index
			++index;
		}
		
		// Otherwise
		else {
		
			// Set index to the first entry
			index = 0;
		}
	}
	
	// Set entry at index to the value
	entries[index] = {key, value};
}

// Set unique and get index
template<typename ValueType, const uint32_t size> uint32_t HashTable<ValueType, size>::setUniqueAndGetIndex(const uint32_t key, const ValueType *value) {

	// Get key's index
	uint32_t index = key % (sizeof(entries) / sizeof(entries[0]));
	
	// Loop while entry at index exists
	while(entries[index].value) {
	
		// Check if index isn't for the last entry
		if(index != (sizeof(entries) / sizeof(entries[0])) - 1) {
		
			// Increment index
			++index;
		}
		
		// Otherwise
		else {
		
			// Set index to the first entry
			index = 0;
		}
	}
	
	// Set entry at index to the value
	entries[index] = {key, value};
	
	// Return index
	return index;
}

// Replace
template<typename ValueType, const uint32_t size> const ValueType *HashTable<ValueType, size>::replace(const uint32_t key, const ValueType *value) {

	// Get key's index
	uint32_t index = key % (sizeof(entries) / sizeof(entries[0]));
	
	// Loop while entry at index exists
	while(entries[index].value) {
	
		// Check if entry has the same key
		if(entries[index].key == key) {
		
			// Get current value
			const ValueType *currentValue = entries[index].value;
			
			// Set entry at index to the value
			entries[index].value = value;
			
			// Return current value
			return currentValue;
		}
		
		// Check if index isn't for the last entry
		if(index != (sizeof(entries) / sizeof(entries[0])) - 1) {
		
			// Increment index
			++index;
		}
		
		// Otherwise
		else {
		
			// Set index to the first entry
			index = 0;
		}
	}
	
	// Set entry at index to the value
	entries[index] = {key, value};
	
	// Return nothing
	return nullptr;
}

// Remove most recent set unique
template<typename ValueType, const uint32_t size> void HashTable<ValueType, size>::removeMostRecentSetUique(const uint32_t index) {

	// Clear entry at index
	entries[index].value = nullptr;
}

// Clear
template<typename ValueType, const uint32_t size> void HashTable<ValueType, size>::clear() {

	// Clear entries
	memset(entries, 0, sizeof(entries));
}

// Contains
template<typename ValueType, const uint32_t size> bool HashTable<ValueType, size>::contains(const uint32_t key) const {

	// Go through all existing entries starting at the key's index
	for(uint32_t index = key % (sizeof(entries) / sizeof(entries[0])); entries[index].value;) {
	
		// Check if entry has the same key
		if(entries[index].key == key) {
		
			// Return true
			return true;
		}
		
		// Check if index isn't for the last entry
		if(index != (sizeof(entries) / sizeof(entries[0])) - 1) {
		
			// Increment index
			++index;
		}
		
		// Otherwise
		else {
		
			// Set index to the first entry
			index = 0;
		}
	}
	
	// Return false
	return false;
}

// Get
template<typename ValueType, const uint32_t size> const ValueType *HashTable<ValueType, size>::get(const uint32_t key) const {

	// Go through all existing entries starting at the key's index
	for(uint32_t index = key % (sizeof(entries) / sizeof(entries[0])); entries[index].value;) {
	
		// Check if entry has the same key
		if(entries[index].key == key) {
		
			// Return entry's value
			return entries[index].value;
		}
		
		// Check if index isn't for the last entry
		if(index != (sizeof(entries) / sizeof(entries[0])) - 1) {
		
			// Increment index
			++index;
		}
		
		// Otherwise
		else {
		
			// Set index to the first entry
			index = 0;
		}
	}
	
	// Return nothing
	return nullptr;
}

// Get values
template<typename ValueType, const uint32_t size> void HashTable<ValueType, size>::getValues(ValueType *values) const {

	// Go through all entries
	for(uint32_t index = 0, valuesIndex = 0; index < (sizeof(entries) / sizeof(entries[0])); ++index) {
	
		// Check if entry exists
		if(entries[index].value) {
		
			// Set value in values
			values[valuesIndex++] = *entries[index].value;
		}
	}
}


#endif
