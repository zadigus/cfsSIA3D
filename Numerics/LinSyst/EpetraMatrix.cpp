#include "EpetraMatrix.hpp"

#include <numeric>
#include <ostream>

// Epetra
#include "Epetra_SerialComm.h"
#include "Epetra_Map.h"
#include "Epetra_CrsGraph.h"
#include "Epetra_CrsMatrix.h"

// Logs
#include "Utility/Logger/Logger.hpp"

namespace N_Mathematics {

	EpetraMatrix::EpetraMatrix(std::vector<int>&& aNnz, std::vector<int>&& aColIdx)
		: IMatrix() //aNnz.size()-1)
	{
		int size(aNnz.size() - 1);
		Epetra_SerialComm comm; // TODO: maybe make this a bit more "parallel-ready"; but the whole code should be upgraded
		Epetra_Map map(size, 0, comm);

		// build up Epetra compatible array of number of non-zeroes; this computes aNnz[i+1]-aNnz[i] for each i
		std::vector<int> numIdxPerRow(aNnz.size());
		std::adjacent_difference(aNnz.begin(), aNnz.end(), numIdxPerRow.begin()); // this is slightly less efficient than a for loop but I'm learning the STL, so ...

		Epetra_CrsGraph graph(Copy, map, &numIdxPerRow[1]); // numIdxPerRow[0] = 0 and is of no use here

		int err(0);
		for (int i(0); i < size; ++i)
		{
			err += !(graph.InsertGlobalIndices(i, numIdxPerRow[i + 1], &aColIdx[aNnz[i]]) == 0); // numIdxPerRow[i+1] = number of indices in row i
		}
		
		if (err)
		{
			LOG_ERR("The matrix's graph could not be filled correctly.");
			exit(EXIT_FAILURE);
		}

		graph.FillComplete();
		m_Data.reset(new Epetra_CrsMatrix(Copy, graph)); 
		
		LOG_INF("Created EpetraMatrix of size " << MS());
	}

	EpetraMatrix::~EpetraMatrix()
	{

	}
	
	int EpetraMatrix::MS()
	{
		return m_Data->Map().NumGlobalElements();
	}

	std::shared_ptr<Epetra_CrsMatrix> EpetraMatrix::get()
	{
		return m_Data;
	}

	int EpetraMatrix::setRow(int aRowNb, const std::vector<double>& aValues, const std::vector<int>& aColIdx)
	{
		return m_Data->ReplaceGlobalValues(aRowNb, aValues.size(), &aValues[0], &aColIdx[0]);
	}

	void EpetraMatrix::print(std::string aFileName)
	{
		std::ofstream ofs(aFileName.c_str(), std::ios_base::app);
		m_Data->Print(ofs);
		ofs.close();
	}

}