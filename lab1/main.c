#include <stdio.h>
#include <memory.h>

#include "database.h"

void demo_func() {
    struct db_session session = db_session_init(
            S_FILE_DEFAULT,
            S_INDEX_TABLE_DEFAULT,
            R_FILE_DEFAULT,
            R_INDEX_TABLE_DEFAULT,
            SR_FILE_DEFAULT
    );
    {
        struct brand_data to_insert = {"some name", 2000, "USA"};
        struct brand_data to_update = {"some name", 2001, "USA"};
        insert_m_brand(&session, to_insert);
        insert_m_brand(&session, to_insert);
        update_m_brand(&session, 2, to_update);
        print_brand(get_m_brand(&session, 1));


        struct factory_data to_insert_factory = {"some name",  "USA", 50000};
        struct factory_data to_update_factory = {"some name",  "USA", 40000};
        insert_m_factory(&session, to_insert_factory);
        insert_m_factory(&session, to_insert_factory);
        update_m_factory(&session, 1, to_update_factory);

        struct model_data to_insert_model = {"some model", 2010};
        insert_s(&session, 1, 2, to_insert_model);
        insert_s(&session, 1, 1, to_insert_model);
        insert_s(&session, 2, 1, to_insert_model);

        struct model_data to_update_model = {"some updated model", 2010};
        update_s(&session, 1, 1, to_update_model);
        ut_s(&session);

//        del_s(&session, 1, 2);
//        del_s(&session, 1, 1);

        del_m_brand(&session, 2);
        del_m_factory(&session, 1);

        ut_m_brand(&session);

        ut_m_factory(&session);

        ut_s(&session);
        print_factory(get_m_factory(&session, 1));


        struct model got_model = get_s(&session, 1, 1);
        printf("name: %s \nyear: %d \n",
               got_model.data.name,
               got_model.data.year);
    }

}

int cmp_str(const char *lhs, const char *rhs, int size) {
    for (int i = 0
            ; i < size; ++i) {
        if (lhs[i] != rhs[i]) {
            return 0;
        }
    }
    return 1;
}


int main() {
    struct db_session session = db_session_init(
            S_FILE_DEFAULT,
            S_INDEX_TABLE_DEFAULT,
            R_FILE_DEFAULT,
            R_INDEX_TABLE_DEFAULT,
            SR_FILE_DEFAULT
    );
    while(1) {
        printf("\nAUTOMOTIVE DATABASE:$ ");
        char cmd[10];
        scanf("%s", cmd);
        if (cmp_str(cmd, "quit", 4)) {
            break;
        } else if (cmp_str(cmd, "reset", 5)) {
            reset_default_db();
            printf("\nDB reset");
        } else if (cmp_str(cmd, "insert_m", 8)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "brand", 5)) {
                struct brand_data input;
                scanf("%s %d %s", input.name, &input.foundation, input.country);
                int id = insert_m_brand(&session, input);
                printf("\ninserted with id=%d", id);
            } else if (cmp_str(table, "factory", 7)) {
                struct factory_data input;
                scanf("%s %d %s", input.name, &input.average_productivity, input.country);
                int id = insert_m_factory(&session, input);
                printf("\ninserted with id=%d", id);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "insert_s", 8)) {
            struct model input;
            scanf("%d %d %s %d", &input.id_brand, &input.id_factory, input.data.name, &input.data.year);
            if (insert_s(&session, input.id_brand, input.id_factory, input.data)) {
                printf("\ninserted successfully");
            } else {
                printf("\nerror while inserting");
            }
        } else if (cmp_str(cmd, "get_m", 5)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "brand", 5)) {
                int id;
                scanf("%d", &id);
                struct brand got = get_m_brand(&session, id);
                print_brand(got);
            } else if (cmp_str(table, "factory", 7)) {
                int id;
                scanf("%d", &id);
                struct factory got = get_m_factory(&session, id);
                print_factory(got);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "get_s", 5)) {
            int id1, id2;
            scanf("%d %d", &id1, &id2);
            struct model got = get_s(&session, id1, id2);

            if (got.id_brand == -1) {
                printf("\nno such model");
            } else {
                print_model(got);
            }
        } else if (cmp_str(cmd, "update_m", 8)) {
            char table[10];
            scanf("%s", table);
            int id;
            if (cmp_str(table, "brand", 5)) {
                struct brand_data input;
                scanf("%d %s %d %s", &id, input.name, &input.foundation, input.country);
                update_m_brand(&session, id, input);
                printf("\nupdated");
            } else if (cmp_str(table, "factory", 7)) {
                struct factory_data input;
                scanf("%d %s %d %s", &id, input.name, &input.average_productivity, input.country);
                update_m_factory(&session, id, input);
                printf("\nupdated", id);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "update_s", 8)) {
            struct model input;
            scanf("%d %d %s %d", &input.id_brand, &input.id_factory, input.data.name, &input.data.year);
            if (update_s(&session, input.id_brand, input.id_factory, input.data)) {
                printf("\nupdated successfully");
            } else {
                printf("\nerror while updating");
            }
        } else if (cmp_str(cmd, "del_m", 5)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "brand", 5)) {
                int id;
                scanf("%d", &id);
                del_m_brand(&session, id);
                printf("deleted");
            } else if (cmp_str(table, "factory", 7)) {
                int id;
                scanf("%d", &id);
                del_m_factory(&session, id);
                printf("deleted");
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "del_s", 5)) {
            int id1, id2;
            scanf("%d %d", &id1, &id2);
            del_s(&session, id1, id2);

            printf("deleted");
        } else if (cmp_str(cmd, "ut_m", 4)) {
            char table[10];
            scanf("%s", table);
            if (cmp_str(table, "brand", 5)) {
                ut_m_brand(&session);
            } else if (cmp_str(table, "factory", 7)) {
                ut_m_factory(&session);
            } else {
                printf("\n wrong table name");
            }
        } else if (cmp_str(cmd, "ut_s", 4)) {
            ut_s(&session);
        } else {
            printf("wrong command");
        }
    }

    session_del(&session);

    return 0;
}
