//------------------------------------------------------------------------------
// This code was generated by a tool.
// <auto-generated />
//------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "CLI11.hpp"

#include "QirRuntime.hpp"
#include "QirContext.hpp"

#include "SimFactory.hpp"

using namespace Microsoft::Quantum;
using namespace std;

// Auxiliary functions for interop with Q# Array type.
struct InteropArray
{
    int64_t Size;
    void* Data;

    InteropArray(int64_t size, void* data) :
        Size(size),
        Data(data){}
};

template<typename T>
unique_ptr<InteropArray> CreateInteropArray(vector<T>& v)
{
    unique_ptr<InteropArray> array(new InteropArray(v.size(), v.data()));
    return array;
}

template<typename S, typename D>
void TranslateVector(vector<S>& sourceVector, vector<D>& destinationVector, function<D(S&)> translationFunction)
{
    destinationVector.resize(sourceVector.size());
    transform(sourceVector.begin(), sourceVector.end(), destinationVector.begin(), translationFunction);
}

// Auxiliary functions for interop with Q# Result type.
const char InteropResultZeroAsChar = 0x0;
const char InteropResultOneAsChar = 0x1;
map<string, char> ResultAsCharMap{
    {"0", InteropResultZeroAsChar},
    {"Zero", InteropResultZeroAsChar},
    {"1", InteropResultOneAsChar},
    {"One", InteropResultOneAsChar}
};

extern "C" void UseResultArrayArg(
    InteropArray* ResultArrayArg
); // QIR interop function.

int main(int argc, char* argv[])
{
    CLI::App app("QIR Standalone Entry Point");

    // Initialize simulator.
    unique_ptr<IRuntimeDriver> sim = CreateFullstateSimulator();
    QirContextScope qirctx(sim.get(), false /*trackAllocatedObjects*/);

    // Add the --simulation-output option.
    string simulationOutputFile;
    CLI::Option* simulationOutputFileOpt = app.add_option(
        "--simulation-output",
        simulationOutputFile,
        "File where the output produced during the simulation is written");

    // Add a command line option for each entry-point parameter.
    vector<char> ResultArrayArgCli;
    app.add_option("--ResultArrayArg", ResultArrayArgCli, "Option to provide a value for the ResultArrayArg parameter")
        ->required()
        ->transform(CLI::CheckedTransformer(ResultAsCharMap, CLI::ignore_case));

    // After all the options have been added, parse arguments from the command line.
    CLI11_PARSE(app, argc, argv);

    // Cast parsed arguments to its interop types.
    unique_ptr<InteropArray> ResultArrayArgUniquePtr = CreateInteropArray(ResultArrayArgCli);
    InteropArray* ResultArrayArgInterop = ResultArrayArgUniquePtr.get();

    // Redirect the simulator output from std::cout if the --simulation-output option is present.
    ostream* simulatorOutputStream = &cout;
    ofstream simulationOutputFileStream;
    if (!simulationOutputFileOpt->empty())
    {
        simulationOutputFileStream.open(simulationOutputFile);
        SetOutputStream(simulationOutputFileStream);
        simulatorOutputStream = &simulationOutputFileStream;
    }

    // Execute the entry point operation.
    UseResultArrayArg(
        ResultArrayArgInterop
    );

    // Flush the output of the simulation.
    simulatorOutputStream->flush();
    if (simulationOutputFileStream.is_open())
    {
        simulationOutputFileStream.close();
    }

    return 0;
}
