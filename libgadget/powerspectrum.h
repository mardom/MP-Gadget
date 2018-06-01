#ifndef POWERSPEC_H
#define POWERSPEC_H

#include <stddef.h>
#include <stdint.h>
#include <gsl/gsl_interp.h>

struct _powerspectrum {
    double * kk;
    double * Power;
    int64_t * Nmodes;
    size_t size;
    size_t nalloc;
    size_t nonzero;
    double Norm;
    /*These are for the LRA neutrino code*/
    /*neutrino perturbations*/
    double * Pnu;
    /*log k bins and ratio of Pnu to Pcdm: stored so interpolation is accurate*/
    double * logknu;
    double * Pnuratio;
    double nu_prefac;
    gsl_interp *nu_spline;
    gsl_interp_accel * nu_acc;

};

/*Allocate memory for the power spectrum*/
void powerspectrum_alloc(struct _powerspectrum * PowerSpectrum, const int nbins, const int nthreads, const int MassiveNuLinResp);

/*Zero memory for the power spectrum*/
void powerspectrum_zero(struct _powerspectrum * PowerSpectrum);

/* Sum the different modes on each thread and processor together to get a power spectrum,
 * and fix the units.*/
void powerspectrum_sum(struct _powerspectrum * PowerSpectrum, const double BoxSize_in_cm);

/*Save the power spectrum to a file*/
void powerspectrum_save(struct _powerspectrum * PowerSpectrum, const char * OutputDir, const double Time, const double D1);

/*Save the neutrino power spectrum to a file*/
void powerspectrum_nu_save(struct _powerspectrum * PowerSpectrum, const char * OutputDir, const double Time);
#endif
