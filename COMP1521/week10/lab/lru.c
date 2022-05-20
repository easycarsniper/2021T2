// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


// represent an entry in a simple inverted page table

typedef struct ipt_entry {
    int virtual_page;        // == -1 if physical page free
    int last_access_time;
} ipt_entry_t;


void lru(int n_physical_pages, int n_virtual_pages);
void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


void lru(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof *ipt);
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++) {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
    }

    int virtual_page;
    for (int access_time = 0; scanf("%d", &virtual_page) == 1; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        access_page(virtual_page, access_time, n_physical_pages, ipt);
    }
}


// if virtual_page is not in ipt, the first free page is used
// if there is no free page, the least-recently-used page is evicted
//
// a single line of output describing the page access is always printed
// the last_access_time in ipt is always updated

void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt) {

    // PUT YOUR CODE HERE TO HANDLE THE 3 cases
    //
    // 1) The virtual page is already in a physical page
        //- find location
        //- update time
    //
    // 2) The virtual page is not in a physical page,
    //    and there is free physical page
        //- find first free location
        //-insert vertical page into it
    //
    // 3) The virtual page is not in a physical page,
    //    and there is no free physical page
        //find least_recent_time frame
        //evict it, then loaded vertual page into it
    //
    // don't forgot to update the last_access_time of the virtual_page
    bool free_frame = false;
    int first_free_frame = -1;
    int least_recent_time = access_time + 1;
    int least_recent_time_frame = -1;
    bool page_already_in = false;
    for (int i = 0; i < n_physical_pages; i++) {
        if (ipt[i].virtual_page == virtual_page) {
            // if the virtual page is already in a physical page
            // update the time and return
            page_already_in = true;
            ipt[i].last_access_time = access_time;
            printf("Time %d: virtual page %d -> physical page %d\n", access_time, virtual_page, i);
            return;
        }
        if (ipt[i].virtual_page == -1 && free_frame == false) {
            // if the frame is free
            first_free_frame = i;
            free_frame = true;       
        }
        if (least_recent_time > ipt[i].last_access_time) {
            // find the lowest last access time
            // record the frame
            least_recent_time = ipt[i].last_access_time;
            least_recent_time_frame = i;
        } 
    }
    if (page_already_in == false && free_frame == true) {
        // place page into the first free frame
        ipt[first_free_frame].virtual_page = virtual_page;
        ipt[first_free_frame].last_access_time = access_time;
        printf("Time %d: virtual page %d loaded to physical page %d\n", access_time, virtual_page, first_free_frame);
        return;
    } else {
        int evict_p = ipt[least_recent_time_frame].virtual_page;
        printf("Time %d: virtual page %d  - virtual page %d evicted - loaded to physical page %d\n", access_time, virtual_page, evict_p, least_recent_time_frame);
        ipt[least_recent_time_frame].virtual_page = virtual_page;
        ipt[least_recent_time_frame].last_access_time = access_time;
        return;
    }
}
