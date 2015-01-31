#include "LinSyst.hpp"

// Epetra data structures
#include "Epetra_SerialComm.h"
#include "Epetra_CrsGraph.h"
#include "Epetra_CrsMatrix.h"
#include "Epetra_Vector.h"
#include "Epetra_Map.h"

// Logs
#include "Utility/Logger/Logger.hpp"

// Configuration
#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

    LinSyst::LinSyst(const N_Configuration::SubComponent& aLinSyst)
        : m_Comm(Teuchos::rcp(new Epetra_SerialComm))
        , m_A(nullptr)
        , m_b(nullptr)
        , m_X(nullptr)
	{
        // TODO: customize the linear system here with Stratimikos
	}

	LinSyst::~LinSyst()
	{

	}

    int LinSyst::matrixSize()
    {
        return m_A->Map().NumGlobalElements();
    }

    void LinSyst::setCrs(std::vector<int>&& aNnz, std::vector<int>&& aColIdx)
    {
        Teuchos::RCP<Epetra_CrsGraph> graph(createCrsGraph(std::move(aNnz), std::move(aColIdx)));

        m_A = Teuchos::rcp(new Epetra_CrsMatrix(Copy, *graph));

        LOG_INF("Created Epetra_CrsMatrix of size " << matrixSize());

        m_b = Teuchos::rcp(new Epetra_Vector(m_A->OperatorRangeMap()));
        m_X = Teuchos::rcp(new Epetra_Vector(m_A->OperatorDomainMap()));

        LOG_INF("Created solution and RHS Epetra_Vectors.");

    }

    Teuchos::RCP<Epetra_CrsGraph> LinSyst::createCrsGraph(std::vector<int>&& aNnz, std::vector<int>&& aColIdx)
    {
        // build up Epetra compatible array of number of non-zeroes; this computes aNnz[i+1]-aNnz[i] for each i
        int size(aNnz.size() - 1);
        std::vector<int> numIdxPerRow(aNnz.size());
        std::adjacent_difference(aNnz.begin(), aNnz.end(), numIdxPerRow.begin());

        // create the CrsGraph
        Epetra_Map map(size, 0, *m_Comm);
        Teuchos::RCP<Epetra_CrsGraph> graph(Teuchos::rcp(new Epetra_CrsGraph(Copy, map, &numIdxPerRow[1]))); // numIdxPerRow[0] = 0 and is of no use here

        // fill the CrsGraph
        int err(0);
        for (int i(0); i < size; ++i)
        {
            err += !(graph->InsertGlobalIndices(i, numIdxPerRow[i + 1], &aColIdx[aNnz[i]]) == 0); // numIdxPerRow[i+1] = number of indices in row i
        }

        if (err)
        {
            LOG_ERR("The matrix graph could not be filled correctly.");
            exit(EXIT_FAILURE);
        }

        graph->FillComplete();
        return graph;
    }

    void LinSyst::solve()
    {

    }

}
