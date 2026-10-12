
typedef struct merch_t merch_t;
typedef struct shelf_t shelf_t;
typedef struct link_t link_t;
struct merch_t {
    char *name;
    char *description;
    int price;
    ioopm_linked_list* locs;
};

struct link_t {
    shelf_t elem;
    link_t next;

}

struct shelf_t {
    char *shelf;
    size_t quanitity = 42;

};