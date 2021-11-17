#include "database.h"

#define UTIL_OFFSET 2*sizeof(int)
#define LAST_PK_OFFSET sizeof(int)
#define FILE_SIZE_OFFSET sizeof(int)

#define MODEL_SIZE sizeof(struct model_node)
#define INDEX_ROW_SIZE sizeof(struct index_table)

#define NO_ROW -1

#define GET_FOR_M(row, session, table, entity_id) {                                     \
    fseek(session->table##_s_index_table, 0, SEEK_SET);                                 \
    int current_index_size;                                                             \
    fread(&current_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);    \
    for (int i = 0; i < current_index_size; ++i) {                                      \
        struct index_table index;                                                       \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);               \
        if (index.id == entity_id) {                                                    \
            row = index.row;                                                            \
            fseek(session->table##_s_index_table, -(long)INDEX_ROW_SIZE, SEEK_CUR);     \
            break;                                                                      \
        }                                                                               \
    }                                                                                   \
}

#define INSERT_M(table) {                                                                           \
    reset_files(session);                                                                           \
    int cur_last_id, cur_size;                                                                      \
    fread(&cur_size, FILE_SIZE_OFFSET, 1, session->table##_s_file);                                 \
    fread(&cur_last_id, LAST_PK_OFFSET, 1, session->table##_s_file);                                \
    ++cur_last_id;                                                                                  \
    ++cur_size;                                                                                     \
    fseek(session->table##_s_file, 0L, SEEK_SET);                                                   \
    fwrite(&cur_size, FILE_SIZE_OFFSET, 1, session->table##_s_file);                                \
    fwrite(&cur_last_id, LAST_PK_OFFSET, 1, session->table##_s_file);                               \
                                                                                                    \
    fseek(session->table##_s_file, (cur_size - 1) * (int) sizeof(struct table) , SEEK_CUR);         \
    struct table to_insert = {cur_last_id, data};                                                   \
    fwrite(&to_insert, sizeof(struct table), 1, session->table##_s_file);                           \
                                                                                                    \
    int cur_index_size;                                                                             \
    fread(&cur_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);                    \
    ++cur_index_size;                                                                               \
    fseek(session->table##_s_index_table, 0L, SEEK_SET);                                            \
    fwrite(&cur_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);                   \
    fseek(session->table##_s_index_table, (cur_index_size - 1) * (int) INDEX_ROW_SIZE , SEEK_CUR);  \
    struct index_table index = {cur_last_id, cur_size - 1, -1};                                     \
    fwrite(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                              \
                                                                                                    \
    return cur_last_id;                                                                             \
}

#define GET_M(table) {                                                                  \
    reset_files(session);                                                               \
    int row = NO_ROW;                                                                   \
    GET_FOR_M(row, session, table, id);                                                 \
    struct table result = {-1};                                                         \
    if (row == NO_ROW) {                                                                \
        return result;                                                                  \
    }                                                                                   \
    fseek(session->table##_s_file, UTIL_OFFSET + row * sizeof(struct table), SEEK_SET); \
    fread(&result, sizeof(struct table), 1, session->table##_s_file);                   \
    return result;                                                                      \
}

#define UPDATE_M(table) {                                                               \
reset_files(session);                                                                   \
    int row = NO_ROW;                                                                   \
    GET_FOR_M(row, session, table, id);                                                 \
    if (row == NO_ROW) {                                                                \
        return -1;                                                                      \
    }                                                                                   \
    fseek(session->table##_s_file, UTIL_OFFSET + row * sizeof(struct table), SEEK_SET); \
    struct table to_insert = {id, new_data};                                            \
    fwrite(&to_insert, sizeof(struct table), 1, session->table##_s_file);               \
    return id;                                                                          \
}



struct db_session db_session_init(
        char* brand_s_file,
        char* brand_s_index_table,
        char* factory_s_file,
        char* factory_s_index_table,
        char* sr_file) {
    struct db_session result = {
            fopen(brand_s_file, "rb+"),
            fopen(brand_s_index_table, "rb+"),
            fopen(factory_s_file, "rb+"),
            fopen(factory_s_index_table, "rb+"),
            fopen(sr_file, "rb+")
    };
    return result;
}

void reset_files(struct db_session* session) {
    fseek(session->brand_s_file, 0L, SEEK_SET);
    fseek(session->brand_s_index_table, 0L, SEEK_SET);
    fseek(session->factory_s_file, 0L, SEEK_SET);
    fseek(session->factory_s_index_table, 0L, SEEK_SET);
    fseek(session->sr_file, 0L, SEEK_SET);
}

int insert_m_brand(struct db_session* session, struct brand_data data) {
    INSERT_M(brand)
}

struct brand get_m_brand(struct db_session* session, int id) {
    GET_M(brand)
}

int update_m_brand(struct db_session* session, int id, struct brand_data new_data) {
    UPDATE_M(brand)
}

struct factory get_m_factory(struct db_session *session, int id) {
    GET_M(factory)
}

int insert_m_factory(struct db_session *session, struct factory_data data) {
    INSERT_M(factory)
}

int update_m_factory(struct db_session *session, int id, struct factory_data new_data) {
    UPDATE_M(factory);
}

#define MAP_NEW_RELATION(table, entity_id) {                                                        \
    int table##_index_size;                                                                         \
    fread(&table##_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);                \
    for (int i = 0; i < table##_index_size; ++i) {                                                  \
        struct index_table index;                                                                   \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                           \
        if (index.id == entity_id) {                                                                \
            if (index.first_node_row == NO_ROW) {                                                   \
                index.first_node_row = model_file_size;                                             \
                fseek(session->table##_s_index_table, -(long)INDEX_ROW_SIZE, SEEK_CUR);             \
                fwrite(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                  \
            } else {                                                                                \
                int last_row = index.first_node_row;                                                \
                struct model_node node;                                                             \
                while (last_row != -1) {                                                            \
                    table##_pre_last_row = last_row;                                                \
                    fseek(session->sr_file, FILE_SIZE_OFFSET + last_row * MODEL_SIZE, SEEK_SET);    \
                    fread(&node, MODEL_SIZE, 1, session->sr_file);                                  \
                    last_row = node.next_row_by_##table;                                            \
                    if (last_row == -1) {                                                           \
                         to_insert.prev_row_by_##table = table##_pre_last_row;                      \
                         node.next_row_by_##table = model_file_size;                                \
                         fseek(session->sr_file, -(long)MODEL_SIZE, SEEK_CUR);                      \
                         fwrite(&node, MODEL_SIZE, 1, session->sr_file);                            \
                    }                                                                               \
                }                                                                                   \
            }                                                                                       \
            break;                                                                                  \
        }                                                                                           \
                                                                                                    \
    }                                                                                               \
                                                                                                    \
}


int insert_s(struct db_session* session, int id_1, int id_2, struct model_data data) {
    if (get_s(session, id_1, id_2).id_brand != -1) {
        return 0;
    }
    reset_files(session);
    int model_file_size;
    fread(&model_file_size, FILE_SIZE_OFFSET, 1, session->sr_file);
    fseek(session->sr_file, 0, SEEK_SET);
    struct model_node to_insert = {
            {
                id_1,
                id_2,
                data
            },
            NO_ROW,
            NO_ROW,
            NO_ROW,
            NO_ROW
    };
    int brand_pre_last_row = NO_ROW;
    MAP_NEW_RELATION(brand, id_1);

    int factory_pre_last_row = NO_ROW;
    MAP_NEW_RELATION(factory, id_2);

    fseek(session->sr_file, FILE_SIZE_OFFSET + model_file_size * MODEL_SIZE, SEEK_SET);
    fwrite(&to_insert, MODEL_SIZE, 1, session->sr_file);
    ++model_file_size;

    fseek(session->sr_file, 0, SEEK_SET);
    fwrite(&model_file_size, FILE_SIZE_OFFSET, 1, session->sr_file);
    return 1;
}

#define GET_FIRST_NODE(table, entity_id) {\
    reset_files(session);\
    int table##_index_size;                                                                        \
    fread(&table##_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);               \
    for (int i = 0; i < table##_index_size; ++i) {                                                 \
        struct index_table index;                                                                  \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                          \
        if (index.id == entity_id) {                                                               \
            first_node_row = index.first_node_row;                                                 \
            break;                                                                                 \
        }                                                                                          \
    }                                                                                              \
}

#define FIND_NODE_BY(table, cmp_table, entity_id) { \
    int next_node = first_node_row;\
    while (next_node != NO_ROW) {\
        fseek(session->sr_file, FILE_SIZE_OFFSET + next_node * MODEL_SIZE, SEEK_SET);\
        fread(&current_node, MODEL_SIZE, 1, session->sr_file);\
        next_node = current_node.next_row_by_##table;\
        if (current_node.entity.id_##cmp_table == entity_id) {                           \
            fseek(session->sr_file, -MODEL_SIZE, SEEK_CUR);\
            break;\
        }\
    }           \
}

/// @brief Sets file pointer in position to rewrite relation

struct model_node get_s_node(struct db_session *session, int id_1, int id_2) {
    reset_files(session);
    struct model empty = {-1, -1};
    struct model_node empty_node = {empty};
    int first_node_row = NO_ROW;
    GET_FIRST_NODE(brand, id_1);
    if (first_node_row == NO_ROW) {
        return empty_node;
    }
    struct model_node current_node;
    FIND_NODE_BY(brand, factory, id_2);

    if (current_node.entity.id_factory == id_2) {
        return current_node;
    }

    return empty_node;
}
struct model get_s(struct db_session *session, int id_1, int id_2) {
    return get_s_node(session, id_1, id_2).entity;
}

#define UT_M_FILE(session, table) { \
    int size, last_id;\
    fread(&size, FILE_SIZE_OFFSET, 1, session->table##_s_file);\
    fread(&last_id, LAST_PK_OFFSET, 1, session->table##_s_file);\
    printf("::::::::::::File::" #table "::::::::::\nSize: %d \nLast_PK: %d\n-------------------------------\n", \
                size,               \
                last_id);\
    for (int i = 0; i < size; ++i) {\
        struct table got;\
        fread(&got, sizeof(struct table), 1, session->table##_s_file);                                          \
        printf("__Row__number__%d__\n", i);                        \
        print_##table(got);         \
    }\
    printf("::::::::::::::End::of::file::" #table "::::::::::\n");                     \
}

#define UT_M_INDEX(session, table) { \
    int size;\
    fread(&size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);\
    printf("::::::::::::Index::table::" #table "::::::::::\nSize: %d\n-------------------------------\n", size);\
    for (int i = 0; i < size; ++i) {\
        struct index_table got;\
        fread(&got, INDEX_ROW_SIZE, 1, session->table##_s_index_table);                                          \
        printf("__Row__number__%d__\n", i);                        \
        print_index_table(got);         \
    }\
    printf("::::::::::::::End::of::index::table::" #table "::::::::::\n");                     \
}

void ut_m_brand(struct db_session *session) {
    reset_files(session);
    UT_M_FILE(session, brand)
    UT_M_INDEX(session, brand)
}

void ut_m_factory(struct db_session *session) {
    reset_files(session);
    UT_M_FILE(session, factory)
    UT_M_INDEX(session, factory)
}

void print_brand(struct brand got) {
    printf("id: %d \nname: %s \nfoundation: %d \ncountry: %s\n",
           got.id,
           got.data.name,
           got.data.foundation,
           got.data.country);
}

void print_factory(struct factory got) {
    printf("id: %d \nname: %s \naverage productivity: %d \ncountry: %s\n",
           got.id,
           got.data.name,
           got.data.average_productivity,
           got.data.country);
}

void print_index_table(struct index_table index) {
    printf("id: %d\nrow: %d\nfirst_node_row: %d\n",
           index.id,
           index.row,
           index.first_node_row);
}

void ut_s(struct db_session *session) {
    reset_files(session);
    int size;
    fread(&size, FILE_SIZE_OFFSET, 1, session->sr_file);
    printf("::::::::::::SR::File::Model::::::::::\nSize: %d\n-------------------------------\n", size);
    for (int i = 0; i < size; ++i) {
        struct model_node got;
        fread(&got, MODEL_SIZE, 1, session->sr_file);
        printf("__Row__number__%d__\n", i);
        print_model_node(got);
    }
    printf("::::::::::::End::of::SR::File::Model::::::::::\n");
}

void print_model_node(struct model_node node) {
    printf("Brand id: %d\nFactory id: %d \nName: %s\nYear: %d \n"
           "Next by brand: %d \nPrev by brand: %d \n"
           "Next by factory: %d \nPrev by factory: %d \n",
           node.entity.id_brand,
           node.entity.id_factory,
           node.entity.data.name,
           node.entity.data.year,
           node.next_row_by_brand,
           node.prev_row_by_brand,
           node.next_row_by_factory,
           node.prev_row_by_factory
           );
}

void print_model(struct model data) {
    printf("Brand id: %d\nFactory id: %d \nName: %s\nYear: %d \n",
           data.id_brand, data.id_factory, data.data.name, data.data.year
    );
}

int update_s(struct db_session *session, int id_1, int id_2, struct model_data new_data) {
    struct model_node found = get_s_node(session, id_1, id_2);
    if (found.entity.id_brand == -1) {
        return 0;
    }

    found.entity.data = new_data;

    if (fwrite(&found, MODEL_SIZE, 1, session->sr_file)) {
        return 1;
    }

    return 0;
}

#define GET_INDEX_ROW_FOR_M(session, table, entity_id) {                                             \
    fseek(session->table##_s_index_table, 0, SEEK_SET);                                 \
    int current_index_size;                                                             \
    fread(&current_index_size, FILE_SIZE_OFFSET, 1, session->table##_s_index_table);    \
    for (int i = 0; i < current_index_size; ++i) {                                      \
        struct index_table index;                                                       \
        fread(&index, INDEX_ROW_SIZE, 1, session->table##_s_index_table);               \
        if (index.id == entity_id) {                                                           \
            index_row = index;                                                                    \
            fseek(session->table##_s_index_table, -(long)INDEX_ROW_SIZE, SEEK_CUR);                                 \
            break;                                                                      \
        }                                                                               \
    }                                                                                   \
}

#define GET_NODE(result, node, next_or_prev, table) { \
    fseek(session->sr_file, FILE_SIZE_OFFSET + node.next_or_prev##_row_by_##table * (long)MODEL_SIZE, SEEK_SET);\
    fread(&result, MODEL_SIZE, 1, session->sr_file);  \
    fseek(session->sr_file, -(long)MODEL_SIZE, SEEK_CUR);\
}

#define INDEX_TABLE_REMAP(session, table, entity_id) {\
    struct index_table index_row;\
    GET_INDEX_ROW_FOR_M(session, table, entity_id)\
    deleted_pos = index_row.first_node_row;           \
    index_row.first_node_row = to_delete.next_row_by_##table; \
    fwrite(&index_row, INDEX_ROW_SIZE, 1, session->table##_s_index_table);\
}

#define REMAP_NODE_NEIGHBOUR(node, next_or_prev, prev_or_next, table) { \
    struct model_node neighbour_node;\
    GET_NODE(neighbour_node, node, next_or_prev, table)                 \
    deleted_pos = neighbour_node.prev_or_next##_row_by_##table;                                                       \
    neighbour_node.prev_or_next##_row_by_##table = node.prev_or_next##_row_by_##table;                                \
    fwrite(&neighbour_node, MODEL_SIZE, 1, session->sr_file);                    \
}

#define REMAP_NEIGHBOURS_TO_NEW_POS(node, next_or_prev, prev_or_next, table) { \
    struct model_node neighbour_node;\
    GET_NODE(neighbour_node, node, next_or_prev, table)                 \
    neighbour_node.prev_or_next##_row_by_##table = deleted_pos;\
    fwrite(&neighbour_node, MODEL_SIZE, 1, session->sr_file);                    \
}

#define INDEX_TABLE_SET_POS(session, table, entity_id) {\
    struct index_table index_row;\
    GET_INDEX_ROW_FOR_M(session, table, entity_id)      \
    index_row.first_node_row = deleted_pos;             \
    fwrite(&index_row, INDEX_ROW_SIZE, 1, session->table##_s_index_table);\
}

void del_s(struct db_session *session, int id_1, int id_2) {
    reset_files(session);

    struct model_node to_delete = get_s_node(session, id_1, id_2);

    if (to_delete.entity.id_brand == -1) {
        return;
    }

    int deleted_pos = NO_ROW;
    if (to_delete.prev_row_by_brand == NO_ROW) {
        INDEX_TABLE_REMAP(session, brand, id_1);
    } else {
        REMAP_NODE_NEIGHBOUR(to_delete, prev, next, brand)
    }

    if (to_delete.prev_row_by_factory == NO_ROW) {
        INDEX_TABLE_REMAP(session, factory, id_2);
    } else {
        REMAP_NODE_NEIGHBOUR(to_delete, prev, next, factory)
    }

    if (to_delete.next_row_by_brand != NO_ROW) {
        REMAP_NODE_NEIGHBOUR(to_delete, next, prev, brand)
    }

    if (to_delete.next_row_by_factory != NO_ROW) {
        REMAP_NODE_NEIGHBOUR(to_delete, next, prev, factory)
    }

    int size;
    reset_files(session);
    fread(&size, FILE_SIZE_OFFSET, 1, session->sr_file);
    fseek(session->sr_file, (size - 1) * (long)MODEL_SIZE, SEEK_CUR);
    struct model_node to_replace;
    fread(&to_replace, MODEL_SIZE, 1, session->sr_file);
    if (size != deleted_pos + 1) {
        int id_brand = to_replace.entity.id_brand;
        int id_factory = to_replace.entity.id_factory;

        reset_files(session);

        if (to_replace.prev_row_by_brand == NO_ROW) {
            INDEX_TABLE_SET_POS(session, brand, id_brand);
        } else {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, prev, next, brand)
        }

        if (to_replace.prev_row_by_factory == NO_ROW) {
            INDEX_TABLE_SET_POS(session, factory, id_factory);
        } else {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, prev, next, factory)
        }

        if (to_replace.next_row_by_brand != NO_ROW) {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, next, prev, brand)
        }

        if (to_replace.next_row_by_factory != NO_ROW) {
            REMAP_NEIGHBOURS_TO_NEW_POS(to_replace, next, prev, factory)
        }
    }


    --size;
    fseek(session->sr_file,0, SEEK_SET);
    fwrite(&size, FILE_SIZE_OFFSET, 1, session->sr_file);
    fseek(session->sr_file,deleted_pos * (long)MODEL_SIZE, SEEK_CUR);
    fwrite(&to_replace, MODEL_SIZE, 1, session->sr_file);

}

#define DEL_M(main, secondary) { \
    reset_files(session);\
    int first_node_row = NO_ROW;\
    do {\
        GET_FIRST_NODE(main, id);\
        if (first_node_row != NO_ROW) {\
            fseek(session->sr_file, FILE_SIZE_OFFSET + first_node_row * MODEL_SIZE, SEEK_SET);\
            struct model_node to_delete;\
            fread(&to_delete, MODEL_SIZE, 1, session->sr_file);\
            del_s(session, id, to_delete.entity.id_##secondary);\
        }\
    } while (first_node_row != NO_ROW);\
    int row = NO_ROW;\
    GET_FOR_M(row, session, main, id)\
    int cur_pos = ftell(session->main##_s_index_table);\
    int deleted_index_row = (cur_pos - FILE_SIZE_OFFSET) / INDEX_ROW_SIZE;\
    \
    if (row != NO_ROW) {\
        int size = 0;\
        fread(&size, FILE_SIZE_OFFSET, 1 , session->main##_s_file);\
        --size;\
        fseek(session->main##_s_file, UTIL_OFFSET + (size) * sizeof(struct main), SEEK_SET);\
        struct main to_replace;\
        fread(&to_replace, sizeof(struct main), 1, session->main##_s_file);\
        fseek(session->main##_s_file, 0, SEEK_SET);\
        fwrite(&size, FILE_SIZE_OFFSET, 1, session->main##_s_file);\
        fseek(session->main##_s_file, UTIL_OFFSET + row * sizeof(struct main), SEEK_SET);\
        fwrite(&to_replace, sizeof(struct main), 1, session->main##_s_file);\
        struct index_table index_row;\
        GET_INDEX_ROW_FOR_M(session, main, to_replace.id)\
        index_row.row = row;\
        fwrite(&index_row, INDEX_ROW_SIZE, 1, session->main##_s_index_table);\
        \
        for (int i = deleted_index_row; i < size; ++i) {\
        \
            fseek(session->main##_s_index_table, FILE_SIZE_OFFSET + (i + 1) * INDEX_ROW_SIZE, SEEK_SET);\
            fread(&index_row, INDEX_ROW_SIZE, 1, session->main##_s_index_table);\
            \
            fseek(session->main##_s_index_table, FILE_SIZE_OFFSET + (i) * INDEX_ROW_SIZE, SEEK_SET);\
            fwrite(&index_row, INDEX_ROW_SIZE, 1, session->main##_s_index_table);\
        \
        }\
        \
        fseek(session->main##_s_index_table, 0, SEEK_SET);\
        \
        fwrite(&size, FILE_SIZE_OFFSET, 1, session->main##_s_index_table);\
    }\
}

void del_m_brand(struct db_session *session, int id) {
    DEL_M(brand, factory)
}

void del_m_factory(struct db_session *session, int id) {
    DEL_M(factory, brand)
}

void reset_default_db() {
    FILE* s = fopen(S_FILE_DEFAULT, "w");
    FILE* si = fopen(S_INDEX_TABLE_DEFAULT, "w");
    FILE* r = fopen(R_FILE_DEFAULT, "w");
    FILE* ri = fopen(R_INDEX_TABLE_DEFAULT, "w");
    FILE* sr = fopen(SR_FILE_DEFAULT, "w");

    int zero = 0;
    int ind = 0;
    fwrite(&zero, sizeof(int), 1, s);
    fwrite(&ind, sizeof(int), 1, s);

    fwrite(&zero, sizeof(int), 1, si);

    fwrite(&zero, sizeof(int), 1, r);
    fwrite(&ind, sizeof(int), 1, r);

    fwrite(&zero, sizeof(int), 1, ri);

    fwrite(&zero, sizeof(int), 1, sr);
    fclose(s);
    fclose(si);
    fclose(r);
    fclose(ri);
    fclose(sr);
}

void session_del(struct db_session *session) {
    fclose(session->brand_s_index_table);
    fclose(session->brand_s_file);
    fclose(session->sr_file);
    fclose(session->factory_s_index_table);
    fclose(session->factory_s_file);
}










