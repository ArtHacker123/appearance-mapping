#ifndef _LIBSVM_H
#define _LIBSVM_H

#ifdef __cplusplus
extern "C" {
#endif

struct svm_node
{
	int index;
	double value;
};

struct svm_problem
{
	int l, n;
	double *y;
	struct svm_node **x;
};

enum { C_SVC, KBB, SPOC, EPSILON_SVR };	/* svm_type */
/* The entry "HIK" is added by Jianxin Wu for histogram intersection kernel */
/* A "PLACE_HOLDER" is put (as value 4) to make "HIK" have value 5, keep same as my revision of libsvm */
enum { LINEAR, POLY, RBF, SIGMOID, PLACE_HOLDER, HIK };	/* kernel_type */

struct svm_parameter
{
	int svm_type;
	int kernel_type;
	double degree;	/* for poly */
	double gamma;	/* for poly/rbf/sigmoid */
	double coef0;	/* for poly/sigmoid */

	/* these are for training only */
	double cache_size; /* in MB */
	double eps;	/* stopping criteria */
	double C; /* for C_SVC, KBB, EPSILON_SVR and EPSILON_SVR */
	int nr_weight;		/* for C_SVC, KBB and SPOC */
	int *weight_label;	/* for C_SVC, KBB and SPOC */
	double* weight;		/* for C_SVC, KBB and SPOC */
	double p;	/* for EPSILON_SVR */
	int shrinking;	/* use the shrinking heuristics */
	int qpsize;	/* for C_SVC, KBB and EPSILON_SVR */
	double Cbegin, Cstep;	/* for linear kernel */ 
};

struct BQP
{
	double eps;
        int n;
        double *x, *C, *Q, *p;
};

//
// svm_model
// 
// moved from bsvm.cpp and modified by Jianxin Wu
struct svm_model
{
    struct svm_parameter param;    // parameter
    int nr_class;       // number of classes, = 2 in regression
    int l;          // total #SV
    struct svm_node **SV;      // SVs (SV[l])
    double **sv_coef;   // coefficients for SVs in decision functions (sv_coef[n-1][l])

    // for classification only

    int *label;     // label of each class (label[n])
    int *nSV;       // number of SVs for each class (nSV[n])
                // nSV[0] + nSV[1] + ... + nSV[n-1] = l
    // XXX
    int free_sv;        // 1 if svm_model is created by svm_load_model
                // 0 if svm_model is created by svm_train
};

struct svm_model *svm_train(const struct svm_problem *prob,
			    const struct svm_parameter *param);

int svm_save_model(const char *model_file_name, const struct svm_model *model);

struct svm_model *svm_load_model(const char *model_file_name);

double svm_predict(const struct svm_model *model, const struct svm_node *x);

void svm_destroy_model(struct svm_model *model);

const char *svm_check_parameter(const struct svm_problem *prob, const struct svm_parameter *param);

#ifdef __cplusplus
}
#endif

#endif /* _LIBSVM_H */
