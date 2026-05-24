import SwiftUI

struct ProcessItem: Codable, Identifiable {
    let pid: Int
    let name: String
    var id: Int { pid }
}

final class ProcessStore: ObservableObject {

    @Published var processes: [ProcessItem] = []

    private var jsonURL: URL {
        FileManager.default.currentDirectoryPath
        return URL(fileURLWithPath: FileManager.default.currentDirectoryPath)
            .appendingPathComponent("processes.json")
    }

    func loadProcesses() {
        do {
            let data = try Data(contentsOf: jsonURL)
            let decoded = try JSONDecoder().decode([ProcessItem].self, from: data)

            DispatchQueue.main.async {
                self.processes = decoded
            }
        } catch {
            print("JSON Error:", error)
        }
    }

    func runCmd(pid: Int, command: String) {

        let result = runcmd(Int32(pid), command)

        if result != 0 {
            print("Command failed:", result)
        }

        loadProcesses()
    }

    func refresh() {
        refresh_processes() 
        loadProcesses()
    }
}