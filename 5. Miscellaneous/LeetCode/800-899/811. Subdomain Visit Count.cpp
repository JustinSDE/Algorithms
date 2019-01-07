class Solution {
  public:
    void mapVisits(string &entry, unordered_map<string, int> &result) {
        int index = 0, right = entry.size() - 1, visits = 0;

        // read the integer first, from left to right
        while (isdigit(entry[index]))
            // multiply visits by 10, add the next digit and increment index
            visits *= 10, visits += entry[index] - '0', index += 1;

        // skip the space
        index += 1;

        // now we go from the right to the left and append each
        // char to a string until we go past `index`. When we
        // find a dot, we add/update the current value in our
        // string in the result map.
        string e;
        while (right >= index) {
            if (entry[right] == '.')
                result[e] += visits;

            // append this character to our entry string
            e += entry[right--];
        }

        // add the last entry as well
        result[e] += visits;
    }

    vector<string> subdomainVisits(vector<string> &cpdomains) {
        unordered_map<string, int> counts;

        // map the visits for each domain, noted that each domain will be
        // keyed in reverse in the map - it finds the names from right to left
        for (auto &entry : cpdomains)
            mapVisits(entry, counts);

        vector<string> result;
        for (auto &entry : counts)
            // construct the result value, the map key must be reversed before
            // concatenated considering mapVisits() walks the string from right
            // to left
            result.push_back(to_string(entry.second) + " " +
                             string(entry.first.rbegin(), entry.first.rend()));

        return result;
    }
};