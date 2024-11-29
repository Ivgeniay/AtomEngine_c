#include "kmemory.h"
#include "core/logger.h"
#include "platform/platform.h"

// TODO: Make custom string library.
#include <string.h> 
#include <stdio.h>


static struct memory_stats stats;
static u8 IsInitialized = FALSE; 

void initialize_memory() {
    if (IsInitialized) {
        //KFATAL("Memory system already initialized.");
        return;
    }

    platform_zero_memory(&stats, sizeof(struct memory_stats));
    IsInitialized = TRUE;
}

void shutdown_memory() {

}

void* kallocate(u64 size, memory_tag tag){
    if (tag == MEMORY_TAG_UNKNOWN){
        KWARN("Attempted to allocate memory with unknown tag.");
    }

    // TODO: Add memory alignment support.
    void* block = platform_allocate(size, FALSE);
 
    if(block){
        stats.total_allocated += size;
        stats.tagged_allocated[tag] += size;
        platform_zero_memory(block, size);

        return block;
    }
    else {
        KERROR("Failed to allocate memory of size %llu with tag %d", size, tag);
        return (void*)0;
    }
}


void kfree(void* ptr, u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) {
        KWARN("Attempted to free memory with unknown tag.");
    }

    stats.total_allocated -= size;
    stats.tagged_allocated[tag] -= size;

    // TODO: Add memory alignment support.
    platform_free(ptr, FALSE);
}


void* kzero_memory(void* block, u64 size) {
    return platform_zero_memory(block, size);
}

void* kcopy_memory(void* dest, const void* src, u64 size) {
    return platform_copy_memory(dest, src, size);
}

void* kset_memory(void* dest, i32 value, u64 size) {
    return platform_set_memory(dest, value, size);
}


char* get_memory_usage_str() {
    const u64 gb = 1024 * 1024 * 1024;
    const u64 mb = 1024 * 1024;
    const u64 kb = 1024;
    
    const u32 buffer_size = 8 * kb;
    static char buffer[buffer_size] = "SYSTEM MEMORY USAGE:\n";
    u64 offset = strlen(buffer);
    
    for(u32 i = 0; i < MEMORY_TAG_MAX_TAGS; i++) {
        char uint[3] = "_b";
        float amount = 1.0f;

        if (stats.tagged_allocated[i] > gb) {
            uint[0] = 'G';
            amount = (float)stats.tagged_allocated[i] / (float)gb; 
        }
        else if (stats.tagged_allocated[i] > mb) {
            uint[0] = 'M';
            amount = (float)stats.tagged_allocated[i] / (float)mb; 
        }
        else if (stats.tagged_allocated[i] > kb) {
            uint[0] = 'K';
            amount = (float)stats.tagged_allocated[i] / (float)kb; 
        }
        else {
            uint[0] = 'B';
            uint[1] = '0';
            amount = (float)stats.tagged_allocated[i];
        }

        i32 length = snprintf(buffer + offset, buffer_size, "  %s: %.2f %s\n", memory_tag_strings[i], amount, uint);
        offset += length;
    }

    char* out_string = _strdup(buffer);
    return out_string;
}