// Copyright (C) 2005, International Business Machines
// Corporation and others.  All Rights Reserved.
#ifndef CoinModel_H
#define CoinModel_H

#include "CoinModelUseful.hpp"

/** 
    This is a simple minded model which is stored in a format which makes
    it easier to construct and modify but not efficient for algorithms.  It has
    to be passed across to ClpModel or OsiSolverInterface by addRows, addCol(umn)s
    or loadProblem.

    It may have up to four parts -
    1) A matrix of doubles (or strings - see note A)
    2) Column information including integer information and names
    3) Row information including names
    4) Quadratic objective

    This class is meant to make it more efficient to build a model.  It is at
    its most efficient when all additions are done as addRow or as addCol but
    not mixed.  If only 1 and 2 exist then solver.addColumns may be used to pass to solver,
    if only 1 and 3 exist then solver.addRows may be used.  Otherwise solver.loadProblem
    must be used.

    If addRows and addColumns are mixed or if individual elements are set then the
    speed will drop to some extent and more memory will be used.

    It is also possible to iterate over existing elements and to access columns and rows
    by name.  Again each of these use memory and cpu time.  However memory is unlikely
    to be critical as most algorithms will use much more.

    Notes:
    A)  Although this could be used to pass nonlinear information around the
        only use at present is to have named values e.g. value1 which can then be
        set to a value after model is created.  I have no idea whether that could
        be useful but I thought it might be fun.
    B)  This class could be useful for modeling.
*/

class CoinModel {
  
public:
  /**@name Useful methods for building model */
   //@{
   /** add a row -  numberInRow may be zero */
   void addRow(int numberInRow, const int * columns,
	       const double * elements, double rowLower=-COIN_DBL_MAX, 
              double rowUpper=COIN_DBL_MAX, const char * name=NULL);
  /// add a column - numberInColumn may be zero */
   void addColumn(int numberInColumn, const int * rows,
                  const double * elements, 
                  double columnLower=0.0, 
                  double columnUpper=COIN_DBL_MAX, double objectiveValue=0.0,
                  const char * name=NULL, bool isInteger=false);
  /// add a column - numberInColumn may be zero */
  inline void addCol(int numberInColumn, const int * rows,
                     const double * elements, 
                     double columnLower=0.0, 
                     double columnUpper=COIN_DBL_MAX, double objectiveValue=0.0,
                     const char * name=NULL, bool isInteger=false)
  { addColumn(numberInColumn, rows, elements, columnLower, columnUpper, objectiveValue,
              name,isInteger);};
  /// Sets value for row i and column j 
  inline void operator() (int i,int j,double value) 
  { setElement(i,j,value);};
  /// Sets value for row i and column j 
  void setElement(int i,int j,double value) ;
  /// Sets quadratic value for column i and j 
  void setQuadraticElement(int i,int j,double value) ;
  /// Sets value for row i and column j as string
  inline void operator() (int i,int j,const char * value) 
  { setElement(i,j,value);};
  /// Sets value for row i and column j as string
  void setElement(int i,int j,const char * value) ;
  /// Associates a string with a value.  Returns string id (or -1 if does not exist)
  int associateElement(const char * stringValue, double value);
  /** Sets rowLower (if row does not exist then
      all rows up to this are defined with default values and no elements)
  */
  void setRowLower(int whichRow,double rowLower); 
  /** Sets rowUpper (if row does not exist then
      all rows up to this are defined with default values and no elements)
  */
  void setRowUpper(int whichRow,double rowUpper); 
  /** Sets rowLower and rowUpper (if row does not exist then
      all rows up to this are defined with default values and no elements)
  */
  void setRowBounds(int whichRow,double rowLower,double rowUpper); 
  /** Sets name (if row does not exist then
      all rows up to this are defined with default values and no elements)
  */
  void setRowName(int whichRow,const char * rowName); 
  /** Sets columnLower (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  void setColumnLower(int whichColumn,double columnLower); 
  /** Sets columnUpper (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  void setColumnUpper(int whichColumn,double columnUpper); 
  /** Sets columnLower and columnUpper (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  void setColumnBounds(int whichColumn,double columnLower,double columnUpper); 
  /** Sets columnObjective (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  void setColumnObjective(int whichColumn,double columnObjective); 
  /** Sets name (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  void setColumnName(int whichColumn,const char * columnName); 
  /** Sets integer (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  void setColumnIsInteger(int whichColumn,bool columnIsInteger); 
  /** Sets columnLower (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  inline void setColLower(int whichColumn,double columnLower) 
  { setColumnLower( whichColumn, columnLower);}; 
  /** Sets columnUpper (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  inline void setColUpper(int whichColumn,double columnUpper) 
  { setColumnUpper( whichColumn, columnUpper);}; 
  /** Sets columnLower and columnUpper (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  inline void setColBounds(int whichColumn,double columnLower,double columnUpper) 
  { setColumnBounds( whichColumn, columnLower, columnUpper);}; 
  /** Sets columnObjective (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  inline void setColObjective(int whichColumn,double columnObjective) 
  { setColumnObjective( whichColumn, columnObjective);}; 
  /** Sets name (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  inline void setColName(int whichColumn,const char * columnName) 
  { setColumnName( whichColumn, columnName);}; 
  /** Sets integer (if column does not exist then
      all columns up to this are defined with default values and no elements)
  */
  inline void setColIsInteger(int whichColumn,bool columnIsInteger) 
  { setColumnIsInteger( whichColumn, columnIsInteger);}; 
  /** Deletes all entries in row and bounds.  If last row the number of rows
      will be decremented and true returned.  */
  bool deleteRow(int whichRow);
  /** Deletes all entries in column and bounds.  If last column the number of columns
      will be decremented and true returned.  */
  bool deleteColumn(int whichColumn);
  /** Deletes all entries in column and bounds.  If last column the number of columns
      will be decremented and true returned.  */
  inline bool deleteCol(int whichColumn)
  { return deleteColumn(whichColumn);};
  /** Packs down all rows i.e. removes empty rows permanently.  Empty rows
      have no elements and feasible bounds. returns number of rows deleted. */
  int packRows();
  /** Packs down all columns i.e. removes empty columns permanently.  Empty columns
      have no elements and no objective. returns number of columns deleted. */
  int packColumns();
  /** Packs down all columns i.e. removes empty columns permanently.  Empty columns
      have no elements and no objective. returns number of columns deleted. */
  inline int packCols()
  { return packColumns();};
  /** Packs down all rows and columns.  i.e. removes empty rows and columns permanently.
      Empty rows have no elements and feasible bounds.
      Empty columns have no elements and no objective.
      returns number of rows+columns deleted. */
  int pack();

  /** Write the problem in MPS format to a file with the given filename.
      
  \param compression can be set to three values to indicate what kind
  of file should be written
  <ul>
  <li> 0: plain text (default)
  <li> 1: gzip compressed (.gz is appended to \c filename)
  <li> 2: bzip2 compressed (.bz2 is appended to \c filename) (TODO)
  </ul>
  If the library was not compiled with the requested compression then
  writeMps falls back to writing a plain text file.
  
  \param formatType specifies the precision to used for values in the
  MPS file
  <ul>
  <li> 0: normal precision (default)
  <li> 1: extra accuracy
  <li> 2: IEEE hex
  </ul>
  
  \param numberAcross specifies whether 1 or 2 (default) values should be
  specified on every data line in the MPS file.
  
  not const as may change model e.g. fill in default bounds
  */
  int writeMps(const char *filename, int compression = 0,
               int formatType = 0, int numberAcross = 2) ;
  
   //@}


  /**@name For getting information */
   //@{
   /// Return number of rows or maximum found so far
  inline int numberRows() const
  { return numberRows_;};
   /// Return number of columns or maximum found so far
  inline int numberColumns() const
  { return numberColumns_;};
   /// Return number of elements
  inline CoinBigIndex numberElements() const
  { return numberElements_;};
  /// Returns value for row i and column j
  inline double operator() (int i,int j) const
  { return getElement(i,j);};
  /// Returns value for row i and column j
  double getElement(int i,int j) const;
  /// Returns quadratic value for columns i and j
  double getQuadraticElement(int i,int j) const;
  /// Returns value for row i and column j as string
  const char * getElementAsString(int i,int j) const;
  /** Returns pointer to element for row i column j.
      Only valid until next modification. 
      NULL if element does not exist */
  double * pointer (int i,int j) const;
  
  
  /** Returns first element in given row - index is -1 if none.
      Index is given by .index and value by .value
  */
  CoinModelLink firstInRow(int whichRow) const ;
  /** Returns last element in given row - index is -1 if none.
      Index is given by .index and value by .value
  */
  CoinModelLink lastInRow(int whichRow) const ;
  /** Returns first element in given column - index is -1 if none.
      Index is given by .index and value by .value
  */
  CoinModelLink firstInColumn(int whichColumn) const ;
  /** Returns last element in given column - index is -1 if none.
      Index is given by .index and value by .value
  */
  CoinModelLink lastInColumn(int whichColumn) const ;
  /** Returns next element in current row or column - index is -1 if none.
      Index is given by .index and value by .value.
      User could also tell because input.next would be NULL
  */
  CoinModelLink next(CoinModelLink & current) const ;
  /** Returns previous element in current row or column - index is -1 if none.
      Index is given by .index and value by .value.
      User could also tell because input.previous would be NULL
  */
  CoinModelLink previous(CoinModelLink & current) const ;
  /** Returns first element in given quadratic column - index is -1 if none.
      Index is given by .index and value by .value
  */
  CoinModelLink firstInQuadraticColumn(int whichColumn) const ;
  /** Returns last element in given quadratic column - index is -1 if none.
      Index is given by .index and value by .value
  */
  CoinModelLink lastInQuadraticColumn(int whichColumn) const ;
  /** Gets rowLower (if row does not exist then -COIN_DBL_MAX)
  */
  double  getRowLower(int whichRow) const ; 
  /** Gets rowUpper (if row does not exist then +COIN_DBL_MAX)
  */
  double  getRowUpper(int whichRow) const ; 
  /** Gets name (if row does not exist then "")
  */
  const char * getRowName(int whichRow) const ; 
  /** Gets columnLower (if column does not exist then 0.0)
  */
  double  getColumnLower(int whichColumn) const ; 
  /** Gets columnUpper (if column does not exist then COIN_DBL_MAX)
  */
  double  getColumnUpper(int whichColumn) const ; 
  /** Gets columnObjective (if column does not exist then 0.0)
  */
  double  getColumnObjective(int whichColumn) const ; 
  /** Gets name (if column does not exist then "")
  */
  const char * getColumnName(int whichColumn) const ; 
  /** Gets if integer (if column does not exist then false)
  */
  bool getColumnIsInteger(int whichColumn) const ; 
  /** Gets columnLower (if column does not exist then 0.0)
  */
  inline double  getColLower(int whichColumn) const
  { return getColumnLower(whichColumn);};
  /** Gets columnUpper (if column does not exist then COIN_DBL_MAX)
  */
  inline double  getColUpper(int whichColumn) const
  { return getColumnUpper(whichColumn) ;};
  /** Gets columnObjective (if column does not exist then 0.0)
  */
  inline double  getColObjective(int whichColumn) const
  { return getColumnObjective(whichColumn);};
  /** Gets name (if column does not exist then "")
  */
  inline const char * getColName(int whichColumn) const
  { return getColumnName(whichColumn);};
  /** Gets if integer (if column does not exist then false)
  */
  inline bool getColIsInteger(int whichColumn) const
  { return getColumnIsInteger(whichColumn);};
  /// Row index from row name (-1 if no names or no match)
  int row(const char * rowName) const;
  /// Column index from column name (-1 if no names or no match)
  int column(const char * columnName) const;
  /// Returns type
  inline int type() const
  { return type_;};
   //@}

  /**@name Constructors, destructor */
   //@{
   /** Default constructor. */
   CoinModel();
   /** Constructor with type 0==for addRow, 1== for addColumn. */
   CoinModel(int type);
   /** Destructor */
   ~CoinModel();
   //@}

   /**@name Copy method */
   //@{
   /** The copy constructor. */
   CoinModel(const CoinModel&);
  /// =
   CoinModel& operator=(const CoinModel&);
   //@}
private:
  /// Resize
  void resize(int maximumRows, int maximumColumns, int maximumElements);
  /// Fill in default row information
  void fillRows(int which,bool forceCreation);
  /// Fill in default column information
  void fillColumns(int which,bool forceCreation);
private:
  /**@name Data members */
   //@{
  /// Current number of rows
  int numberRows_;
  /// Maximum number of rows
  int maximumRows_;
  /// Current number of columns
  int numberColumns_;
  /// Maximum number of columns
  int maximumColumns_;
  /// Current number of elements
  int numberElements_;
  /// Maximum number of elements
  int maximumElements_;
  /// Current number of quadratic elements
  int numberQuadraticElements_;
  /// Maximum number of quadratic elements
  int maximumQuadraticElements_;
  /// Direction of optimization (1 - minimize, -1 - maximize, 0 - ignore
  double optimizationDirection_;
  /// Row lower 
  double * rowLower_;
  /// Row upper 
  double * rowUpper_;
  /// Row names
  CoinModelHash rowName_;
  /** Row types.
      Has information - at present
      bit 0 - rowLower is a string
      bit 1 - rowUpper is a string
  */
  int * rowType_;
  /// Objective
  double * objective_;
  /// Column Lower
  double * columnLower_;
  /// Column Upper
  double * columnUpper_;
  /// Column names
  CoinModelHash columnName_;
  /// Integer information
  int * integerType_;
  /// Strings
  CoinModelHash string_;
  /** Column types.
      Has information - at present
      bit 0 - columnLower is a string
      bit 1 - columnUpper is a string
      bit 2 - objective is a string
      bit 3 - integer setting is a string
  */
  int * columnType_;
  /// If simple then start of each row/column
  int * start_;
  /// Actual elements
  CoinModelTriple * elements_;
  /// Hash for elements
  mutable CoinModelHash2 hashElements_;
  /// Linked list for rows
  mutable CoinModelLinkedList rowList_;
  /// Linked list for columns
  mutable CoinModelLinkedList columnList_;
  /// Actual quadratic elements (always linked lists)
  CoinModelTriple * quadraticElements_;
  /// Hash for quadratic elements
  mutable CoinModelHash2 hashQuadraticElements_;
  /// Array for sorting indices
  int * sortIndices_;
  /// Array for sorting elements
  double * sortElements_;
  /// Size of sort arrays
  int sortSize_;
  /// Linked list for quadratic rows
  mutable CoinModelLinkedList quadraticRowList_;
  /// Linked list for quadratic columns
  mutable CoinModelLinkedList quadraticColumnList_;
  /** Type of build -
      -1 unset,
      0 for row, 
      1 for column,
      2 linked.
  */
  int type_;
  /** Links present (could be tested by sizes of objects)
      0 - none,
      1 - row links,
      2 - column links,
      3 - both
  */
  int links_;
   //@}
};

#endif