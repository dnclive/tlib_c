/*
 * tsql.c
 */

#include <stdlib.h>
#include <string.h>
#include <ibase.h>
#include <stdio.h>
#include "tsql.h"

tsql *tsql_finit()								//инициализация
{
	
}

tsql *tsql_fcre()								//выделение памяти под данные библиотеки
{
	
}


//*******firebird********
tsql *tsql_fb_fcre()
{
	
	char *sel_str =
     "SELECT department, mngr_no, location, head_dept \
      FROM department WHERE head_dept in ('100', '900', '600')";

	isc_db_handle    DB = 0;                       /* database handle */
	isc_tr_handle    trans = 0;                    /* transaction handle */
	ISC_STATUS_ARRAY status;                       /* status vector */
	
	int                num_cols, i;
    isc_stmt_handle    stmt = NULL;
    XSQLDA             *sqlda;
    char               empdb[128];

    //if (argc > 1)
    //     strcpy(empdb, argv[1]);
   // else
    strcpy(empdb, "employee.fdb");

    if (isc_attach_database(status, 0, empdb, &DB, 0, NULL))
    {
        ERREXIT(status, 1);
        //tdeb_fdeb3("tsql_deb", __FILE__, __LINE__, "str_each->chari=%i\r\n", *str_each->chari);
        //return -1;
    }

    /* Allocate SQLDA of an arbitrary size. */
    sqlda = (XSQLDA *) malloc(XSQLDA_LENGTH(3));
    sqlda->sqln = 3;
    sqlda->version = 1;

    if (isc_start_transaction(status, &trans, 1, &DB, 0, NULL))
    {
        ERREXIT(status, 1);
    }

    /* Allocate a statement. */
    if (isc_dsql_allocate_statement(status, &DB, &stmt))
    {
        ERREXIT(status, 1);
    }

    /* Prepare the statement. */
    if (isc_dsql_prepare(status, &trans, &stmt, 0, sel_str, 1, sqlda))
    {
        ERREXIT(status, 1);
    }

    /* Describe the statement. */
    if (isc_dsql_describe(status, &stmt, 1, sqlda))
    {
        ERREXIT(status, 1);
    }
    
    /* This is a select statement, print more information about it. */

    printf("Query Type:  SELECT\n\n");

    num_cols = sqlda->sqld;

    printf("Number of columns selected:  %d\n", num_cols);

    /* Reallocate SQLDA if necessary. */
    if (sqlda->sqln < sqlda->sqld)
    {
        sqlda = (XSQLDA *) malloc(XSQLDA_LENGTH(num_cols));
        sqlda->sqln = num_cols;
        sqlda->version = 1;
    
        /* Re-describe the statement. */
        if (isc_dsql_describe(status, &stmt, 1, sqlda))
        {
            ERREXIT(status, 1);
        }

        num_cols = sqlda->sqld;
    }

    /* List column names, types, and lengths. */
    for (i = 0; i < num_cols; i++)
    {
        printf("\nColumn name:    %s\n", sqlda->sqlvar[i].sqlname);
        printf("Column type:    %d\n", sqlda->sqlvar[i].sqltype);
        printf("Column length:  %d\n", sqlda->sqlvar[i].sqllen);
    }


    if (isc_dsql_free_statement(status, &stmt, DSQL_drop))
    {
        ERREXIT(status, 1);
    }

    if (isc_commit_transaction(status, &trans))
    {
        ERREXIT(status, 1);
    }

    if (isc_detach_database(status, &DB))
    {
        ERREXIT (status, 1);
    }

    free(sqlda);

    return 0;
	
}

