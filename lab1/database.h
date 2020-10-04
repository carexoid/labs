#ifndef DATABASE_PRAGMA_ONCE
#define DATABASE_PRAGMA_ONCE

#include <stdio.h>

#define S_FILE_DEFAULT "S.fl"
#define S_INDEX_TABLE_DEFAULT "S.ind"
#define R_FILE_DEFAULT "R.fl"
#define R_INDEX_TABLE_DEFAULT "R.ind"
#define SR_FILE_DEFAULT "SR.fl"

struct index_table {
    int id;
    int row;
    int first_node_row;
};

void print_index_table(struct index_table index);

struct db_session {
    FILE* brand_s_file;
    FILE* brand_s_index_table;
    FILE* factory_s_file;
    FILE* factory_s_index_table;
    FILE* sr_file;
};

struct db_session db_session_init(
        char* brand_s_file,
        char* brand_s_index_table,
        char* factory_s_file,
        char* factory_s_index_table,
        char* sr_file
);

void session_del(struct db_session*);

struct brand {
    int id;
    struct brand_data {
        char name[32];
        int foundation;
        char country[32];
    } data;
};

void print_brand(struct brand got);

struct factory {
    int id;
    struct factory_data {
        char name[32];
        char country[32];
        int average_productivity;
    } data;
};

void print_factory(struct factory got);

struct model_node {
    struct model {
        int id_brand;
        int id_factory;
        struct model_data{
            char name[32];
            int year;
        } data;
    } entity;

    int prev_row_by_brand;
    int prev_row_by_factory;
    int next_row_by_brand;
    int next_row_by_factory;
};

void print_model(struct model);

void print_model_node(struct model_node);

struct brand get_m_brand(struct db_session* session, int id);

struct factory get_m_factory(struct db_session* session, int id);

struct model get_s(struct db_session* session, int id_1, int id_2);

void del_m_brand(struct db_session* session, int id);

void del_m_factory(struct db_session* session, int id);

void del_s(struct db_session* session, int id_1, int id_2);

int insert_m_brand(struct db_session* session, struct brand_data data);

int insert_m_factory(struct db_session* session, struct factory_data data);

int insert_s(struct db_session* session, int id_1, int id_2, struct model_data data);

int update_m_brand(struct db_session* session, int id, struct brand_data new_data);

int update_m_factory(struct db_session* session, int id, struct factory_data new_data);

int update_s(struct db_session* session, int id_1, int id_2, struct model_data new_data);

void ut_m_brand(struct db_session* session);

void ut_m_factory(struct db_session* session);

void ut_s(struct db_session* session);

void reset_default_db();

#endif