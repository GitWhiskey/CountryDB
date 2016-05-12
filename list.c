#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

const char * DBNAME = "database.csv";
const int MAX_LINE_LENGTH = 150;


/* Тип указателя на функцию для сравнения элементов списка */
typedef int (* CMP_FUNC)(COUNTRY * v1, COUNTRY * v2);

/*
 * Выделяет динамическую память для нового элемента списка list,
 * инициализирует поля и добавляет элемент в начало списка
 * Изменяет указатель на начало списка. Возвращает 0 если новый элемент
 * добавлен или 1 если не удалось выделить память для элемента. 
 */
int add( COUNTRY ** list, char * name, int population, int area)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	COUNTRY * c = (COUNTRY *)malloc(sizeof(COUNTRY));
	if (c) {
		strcpy(c->name, name); 
		c->population = population; c->area = area;
        	c->next = *list;
        	*list = c;
		return 0; /* ok */
    	} 
	return 1;    	
}

/* Удаляет элемент списка list и освобождает выделенную по него память.
 *   Если элемент первый, изменяет указатель на список 
 */
void delete(COUNTRY ** list, COUNTRY * v)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
    COUNTRY * p = *list;
    COUNTRY * prev = NULL;

    while (p != NULL) {
        if (p == v) {
            if (prev) {
                prev->next = p->next;
            }
            else { /* Если prev == NULL, то мы удаляем первый элемент списка */
                *list = p->next;
            }
            free(p); /* Освобождаем память, выделеную под элемент */
            break;
        }
        prev = p;
        p = p->next;
    }	
}

/*
 * Ищет в списке страну с заданным именем name. Возвращает указатель на
 * найденный элеемнт списка или NULL, если страна с таким названием отсутсвует
 * в списке.
 */
COUNTRY * find(COUNTRY * list, char * name)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */

	COUNTRY * p = list;
	while(p!=NULL) {
		if(strcmp(p->name, name)==0) {
			break;
		}
		else {
			p = p->next;
		}
	}
    return p;
}

/*
 * Возвращает количество элементов в списке 
 */
int count(COUNTRY * list)
{
    int cnt = 0;

    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	COUNTRY * p = list;
	while(p!=NULL) {
		cnt++;
		p = p->next;
	}

    return cnt;
}

/* Быстрая сортировка массива указателей на элементы списка */
void quick_sort(COUNTRY ** ca, int first, int last, CMP_FUNC compare)
{
    int i, j;
    COUNTRY * v;
    COUNTRY * p;

    i = first;
    j = last;
    v = ca[(first + last) / 2];

    do {
        while (compare(ca[i], v) < 0) i++;
        while (compare(ca[j], v) > 0) j--;

        if(i <= j) {
            if (compare(ca[i], ca[j]) > 0) {
                p = ca[j];
                ca[j] = ca[i];
                ca[i] = p;
            }
            i++; j--;
        }
    } while (i <= j);

    if (i < last)
        quick_sort(ca, i, last, compare);

    if (first < j)
        quick_sort(ca, first, j, compare);
}

int compare_name(COUNTRY *v1, COUNTRY *v2)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */ 
	return strcmp(v1->name,v2->name);  
}

int compare_area(COUNTRY *v1, COUNTRY *v2)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */  
	if(v1->area > v2->area) 
		return 1;
	else if(v1->area < v2->area)
		return -1;
	else if(v1->area == v2->area)
		return 0;
}

int compare_population(COUNTRY *v1, COUNTRY *v2)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */  
	if(v1->population > v2->population) 
		return 1;
	else if(v1->population < v2->population)
		return -1;
	else if(v1->population == v2->population)
		return 0; 
}

/* 
 * Сортирует список по именам стран в алфавитном порядке методом пузырьковой 
 * сортировки. Указатель на начало списка может измениться в результате   
 * сортировки 
 */
int sort(COUNTRY ** list, CMP_FUNC compare)
{
    int cnt, i;
    COUNTRY *p, **ca = NULL;

    cnt = count(*list);
    if (cnt < 2)
        return 0;
    
    /* выделяем память под массив указателей */
    ca = (COUNTRY **)malloc(cnt*sizeof(COUNTRY *));
    if (!ca)
        return 1;

    /* заполняем массив указателями на элементы списка */
    ca[0] = *list;
    for (i = 1; i < cnt; i++)
        ca[i] = ca[i-1]->next;

    quick_sort(ca, 0, cnt - 1, compare);

    /* заполняем список элементами из отсортированного массива */
    *list = NULL;
    while (cnt > 0) {
        ca[cnt - 1]->next = *list;
        *list = ca[cnt - 1];
        cnt--;
    }
    free(ca);
    return 0;
}


int sort_by_name(COUNTRY ** list)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	return sort(list,compare_name);

}

int sort_by_area(COUNTRY ** list)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	return sort(list,compare_area);
}

int sort_by_population(COUNTRY ** list)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	return sort(list,compare_population);
}

void print_country(COUNTRY * p)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	printf("%s, ", p->name);
	if(p->population == 0)
		printf("не указано, ");
	else
		printf("%d, ", p->population);
	if(p->area == 0)
		printf("не указано\n");
	else
		printf("%d\n", p->area);
}

void dump(COUNTRY * list)
{
    COUNTRY * p;
    p = list; /* Начало списка */
    while (p != NULL) {
        print_country(p);
        p = p->next;
    }
}

/*
 * удаление всех эдементов списка и
 * освобождение выделенной под эти элементы памяти 
 */
void clear(COUNTRY * list)
{
    /* СДЕЛАТЬ:
     * функцию по описанию в тексте задания
     */
	while(list!=NULL) {
		COUNTRY * p = list;
		delete(&list, p);
	}
}

/* Загружает список стран из файла */
COUNTRY * load()
{
    char buf[MAX_LINE_LENGTH + 1];
    char * par[3];
    int cnt, pcount = 0;
    COUNTRY *p, * list = NULL;
    FILE * f = fopen(DBNAME, "r");

    buf[MAX_LINE_LENGTH] = 0x00; 
 
    if (f) {
        while(fgets(buf, MAX_LINE_LENGTH, f)) {
            pcount = 0;
            par[pcount++] = buf;
            cnt = 0;
            while(buf[cnt]) {
                if (buf[cnt] == ',') {
                    buf[cnt] = 0x00;
                    par[pcount++] = &buf[cnt + 1];
                }
                cnt++;
            }
            if (pcount == 3) {
                add(&list, par[0], atoi(par[1]), atoi(par[2])); 
            }           
        }
        fclose(f);
    }
    return list;
}

/* Сохраняет список стран в файл */
void save(COUNTRY * list)
{
    FILE * f = fopen(DBNAME, "w+");
    COUNTRY * p = list;
    if (f) {
        while (p != NULL) {
            fprintf(f, "%s,%d,%d\n", p->name, p->population, p->area);
            p = p->next;
        }
        fclose(f);
    }
}


