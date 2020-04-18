#ifndef TOPPRA_GEOMETRIC_PATH_HPP
#define TOPPRA_GEOMETRIC_PATH_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <toppra/toppra.hpp>
#include <vector>

namespace toppra {
class GeometricPath {
public:
  virtual ~GeometricPath(){};
  /**
   * /brief Evaluate the path at given position.
   */
  virtual Vector eval(value_type, int order = 0)=0;

  /**
   * /brief Evaluate the path at given positions (vector).
   */
  virtual Vectors eval(std::vector<value_type>, int order = 0)=0;

  /**
   * Return the degrees-of-freedom of the path.
   */
  virtual int dof()=0;

  /**
   * Return the starting and ending path positions.
   */
  virtual Vector pathInterval()=0;
};


/**
 * \brief Piecewise polynomial geometric path.
 *
 * A simple implemetation of a piecewise polynoamial geometric path.
 *
 */
class PiecewisePolyPath : public GeometricPath {
public:
  /**
   * Consructor.
   *
   * @param coefficients Polynoamial coefficients.
   * @param breakpoints Vector of breakpoints.
   */
  PiecewisePolyPath(const Matrices &, const std::vector<value_type> &);

  /**
   * /brief Evaluate the path at given position.
   */
  Vector eval(value_type, int order = 0);

  /**
   * /brief Evaluate the path at given positions (vector).
   */
  Vectors eval(std::vector<value_type>, int order = 0);

  /**
   * /brief Evaluate the path at given positions (vector).
   */
  Vectors eval(Vector, int order = 0);

  /**
   * Return the degrees-of-freedom of the path.
   */
  int dof() { return m_coefficients[0].cols(); };

  /**
   * Return the starting and ending path positions.
   */
  Vector pathInterval() {
    Vector v(2);
    v << m_breakpoints[0], m_breakpoints[-1];
    return v;
  };

private:
  size_t findSegmentIndex(value_type pos) const;
  void checkInputArgs();
  void computeDerivativesCoefficients();
  Matrix getCoefficient(int seg_index, int order);
  Matrices m_coefficients, m_coefficients_1, m_coefficients_2;
  std::vector<value_type> m_breakpoints;
  int m_dof, m_degree;
};

} // namespace toppra

#endif
